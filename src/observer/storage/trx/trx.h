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
  TrxEvent() = default;
  virtual ~TrxEvent() = default;
  enum class Type : int {
    INSERT,
    UPDATE,
    DELETE,
  };

public:
  virtual const char *get_table_name() { return ""; };
  virtual RC commit() { return RC::SUCCESS; }
  virtual RC rollback() { return RC::SUCCESS; };
};

class InsertTrxEvent : public TrxEvent {
public:
  InsertTrxEvent(Table *table, Record *new_record)
      : table_(table), new_record_(new_record) {}
  virtual ~InsertTrxEvent();

  const char *get_table_name() { return table_->name(); }
  RC commit() { return table_->commit_insert(new_record_); }
  RC rollback() { return table_->rollback_insert(new_record_); }

private:
  Table *table_;
  Record *new_record_;
};

class DeleteTrxEvent : public TrxEvent {
public:
  DeleteTrxEvent(Table *table, Record *old_record)
      : table_(table), old_record_(old_record) {}
  virtual ~DeleteTrxEvent();

  const char *get_table_name() { return table_->name(); }
  RC commit() { return table_->commit_delete(old_record_); }
  RC rollback() { return table_->rollback_delete(old_record_); }

private:
  Table *table_;
  Record *old_record_;
};

class UpdateTrxEvent : public TrxEvent {
public:
  UpdateTrxEvent(Table *table, Record *old_record, Record *new_record,
                 const FieldMeta &field_meta)
      : table_(table), old_record_(old_record), new_record_(new_record),
        field_meta_(field_meta) {}
  virtual ~UpdateTrxEvent();

  const char *get_table_name() { return table_->name(); }
  RC commit() {
    return table_->commit_update(old_record_, new_record_, field_meta_);
  }
  RC rollback() {
    return table_->rollback_update(old_record_, new_record_, field_meta_);
  }

private:
  Table *table_;
  Record *old_record_;
  Record *new_record_;
  FieldMeta field_meta_;
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
  void pending(TrxEvent *event);
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
