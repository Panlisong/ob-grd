#include <atomic>

#include "common/log/log.h"
#include "storage/common/field_meta.h"
#include "storage/common/record_manager.h"
#include "storage/common/table.h"
#include "storage/trx/trx.h"

Trx::Trx() {}
Trx::~Trx() {}

InsertTrxEvent::~InsertTrxEvent() {
  delete[] new_record_->data;
  delete new_record_;
}
DeleteTrxEvent::~DeleteTrxEvent() {
  delete[] old_record_->data;
  delete old_record_;
}
UpdateTrxEvent::~UpdateTrxEvent() {
  delete[] old_record_->data;
  delete old_record_;
}

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
    rc = trx_event->commit();

    cur_event_index++;
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to commit record data, table=%s, rc=%d:%s",
                trx_event->get_table_name(), rc, strrc(rc));
      rollback();
      break;
    }
    delete trx_event;
  }
  return rc;
}

void Trx::rollback() {
  cur_event_index--;

  RC rc = RC::SUCCESS;
  TrxEvent *trx_event;
  while (cur_event_index >= 0) {
    trx_event = trx_events[cur_event_index];
    rc = trx_event->rollback();

    if (rc != SUCCESS) {
      LOG_PANIC("Failed to rollback, table=%s, rid=%d, rc=%d:%s",
                trx_event->get_table_name(), 0, rc, strrc(rc));
    }
    cur_event_index--;
  }
}
