// TODO: rename marco
#ifndef __OBSERVER_STORAGE_TRX_TRX_H_
#define __OBSERVER_STORAGE_TRX_TRX_H_

#include <list>
#include <mutex>
#include <stddef.h>

#include "rc.h"
#include "sql/parser/parse.h"
#include "storage/common/record_manager.h"
#include "storage/common/table.h"

class TrxEvent {
public:
  enum class Type : int {
    INSERT,
    UPDATE,
    DELETE,
  };

public:
  TrxEvent(Table *table, TrxEvent::Type type, Record *old_record,
           Record *new_record) {
    table_ = table;
    type_ = type;
    old_record_ = old_record;
    new_record_ = new_record;
  }
  ~TrxEvent();

public:
  TrxEvent::Type get_type() { return type_; }
  const char *get_table_name() { return table_->name(); }

  RC commit_insert();
  RC rollback_insert();

  RC commit_delete();
  RC rollback_delete();

  RC commit_update();
  RC rollback_update();

private:
  Table *table_;
  TrxEvent::Type type_;
  Record *old_record_;
  Record *new_record_;
};

class Trx {
public:
  Trx();
  ~Trx();
  static const char *trx_field_name();
  static AttrType trx_field_type();
  static int trx_field_len();

public:
  void begin();
  void pending(Table *table, TrxEvent::Type type, Record *old_record,
               Record *new_record);
  RC commit();
  void rollback();

private:
  static int32_t next_trx_id();

private:
  int32_t trx_id_ = 0;
  std::vector<TrxEvent *> trx_events;
  int cur_event_index = 0;
};

#endif // __OBSERVER_STORAGE_TRX_TRX_H_
