#include <atomic>

#include "common/log/log.h"
#include "storage/common/field_meta.h"
#include "storage/common/record_manager.h"
#include "storage/common/table.h"
#include "storage/trx/trx.h"

static const uint32_t DELETED_FLAG_BIT_MASK = 0x80000000;
// static const uint32_t TRX_ID_BIT_MASK = 0x7FFFFFFF;

Trx::Trx() {}

Trx::~Trx() {}

const char *Trx::trx_field_name() { return "__trx"; }

AttrType Trx::trx_field_type() { return INTS; }

int Trx::trx_field_len() { return sizeof(int32_t); }

int32_t Trx::next_trx_id() {
  static std::atomic<int32_t> trx_id;
  return ++trx_id;
}

void Trx::begin() {
  if (trx_id_ != 0) {
    LOG_ERROR("trx already begin");
    return;
  }
  trx_id_ = next_trx_id();
}

void Trx::pending(TrxEvent *event) { trx_events.push_back(event); }

RC Trx::commit() {
  RC rc = RC::SUCCESS;
  int size = trx_events.size();
  while (cur_event_index < size) {
    TrxEvent *trx_event = trx_events[cur_event_index];
    trx_event->commit();

    cur_event_index++;
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to commit record data, table=%s, rc=%d:%s",
                trx_event->get_table_name(), rc, strrc(rc));
      rollback();
      break;
    }
  }
  return rc;
}

void Trx::rollback() {
  cur_event_index--;

  RC rc = RC::SUCCESS;
  TrxEvent *trx_event;
  while (cur_event_index >= 0) {
    trx_event = trx_events[cur_event_index];
    trx_event->rollback();

    if (rc != SUCCESS) {
      LOG_PANIC("Failed to rollback, table=%s, rid=%d, rc=%d:%s",
                trx_event->get_table_name(), 0, rc, strrc(rc));
    }
    cur_event_index--;
  }
}

InsertTrxEvent::InsertTrxEvent(Table *table, Record *new_record) {
  table_ = table;
  new_record_ = new_record;
}

InsertTrxEvent::~InsertTrxEvent() {}

const char *InsertTrxEvent::get_table_name() { return table_->name(); }

RC InsertTrxEvent::commit() { return table_->commit_insert(new_record_); }

RC InsertTrxEvent::rollback() { return table_->rollback_insert(new_record_); }

DeleteTrxEvent::DeleteTrxEvent(Table *table, Record *old_record) {
  table_ = table;
  old_record_ = old_record;
}

const char *DeleteTrxEvent::get_table_name() { return table_->name(); }

DeleteTrxEvent::~DeleteTrxEvent() {}

RC DeleteTrxEvent::commit() { return table_->commit_delete(old_record_); }

RC DeleteTrxEvent::rollback() { return table_->rollback_delete(old_record_); }
