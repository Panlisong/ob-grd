#ifndef __OBSERVER_SQL_PARSE_SYMBOL_TABLE_H__
#define __OBSERVER_SQL_PARSE_SYMBOL_TABLE_H__

#include <list>
#include <memory>
#include <unordered_map>

template <class SYM, class DAT> class SymbolTable {
  typedef std::unordered_map<SYM, DAT *> Scope;
  typedef std::list<std::shared_ptr<Scope>> ScopeList;

private:
  ScopeList *head_;

public:
  SymbolTable() : head_(new ScopeList) {}

  ~SymbolTable() {
    for (auto scope : *head_) {
      scope.reset();
    }
    delete head_;
  }

  SymbolTable &operator=(const SymbolTable &other) {
    head_->clear();
    for (auto scope : *other.head_) {
      head_->push_back(scope);
    }
    return *this;
  }

  bool empty() { return head_->empty(); }

  void enterscope() { head_->push_front(std::make_shared<Scope>()); }

  void exitscope() { head_->pop_front(); }

  std::shared_ptr<Scope> head() { return head_->front(); }

  void add_id(SYM s, DAT *data) { head_->front()->insert({s, data}); }

  DAT *lookup(SYM s) {
    for (auto scope : *head_) {
      auto res = scope->find(s);
      if (res != scope->end()) {
        return res->second;
      }
    }
    return nullptr;
  }

  DAT *probe(SYM s) {
    auto cur = head_->front();
    auto res = cur->find(s);
    if (res != cur->end()) {
      return res->second;
    }
    return nullptr;
  }
};

#endif //__OBSERVER_SQL_PARSE_SYMBOL_TABLE_H__