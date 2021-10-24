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

void Trx::pending(Table *table, TrxEvent::Type type, Record *old_record,
                  Record *new_record) {
  const FieldMeta *trx_field = table->table_meta().trx_field();

  if (type == TrxEvent::Type::DELETE) {
    int32_t *ptrx_id = (int32_t *)(old_record->data + trx_field->offset());
    *ptrx_id = DELETED_FLAG_BIT_MASK | trx_id_;
  } else {
    int32_t *ptrx_id = (int32_t *)(new_record->data + trx_field->offset());
    *ptrx_id = trx_id_;
  }
  TrxEvent *trx_event = new TrxEvent(table, type, old_record, new_record);
  trx_events.push_back(trx_event);
}

RC Trx::commit() {
  RC rc = RC::SUCCESS;
	int size= trx_events.size();
  while (cur_event_index < size){
    TrxEvent *trx_event = trx_events[cur_event_index];
    switch (trx_event->get_type()) {
    case TrxEvent::Type::INSERT: {
      rc = trx_event->commit_insert();
    } break;
    case TrxEvent::Type::DELETE: {
      rc = trx_event->commit_delete();
    } break;
    case TrxEvent::Type::UPDATE: {
      rc = trx_event->commit_update();
    } break;
    default: {
    } break;
    };

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
    switch (trx_event->get_type()) {
    case TrxEvent::Type::INSERT: {
      rc = trx_event->rollback_insert();
    } break;
    case TrxEvent::Type::DELETE: {
      rc = trx_event->rollback_delete();
    } break;
    case TrxEvent::Type::UPDATE: {
      rc = trx_event->rollback_update();
    } break;
    }

    if (rc != SUCCESS) {
      LOG_PANIC("Failed to rollback, table=%s, rid=%d, rc=%d:%s",
                trx_event->get_table_name(), 0, rc, strrc(rc));
    }
    cur_event_index--;
  }
}

RC TrxEvent::commit_insert() { return table_->commit_insert(new_record_); }

RC TrxEvent::rollback_insert() { return table_->rollback_insert(new_record_); }

RC TrxEvent::commit_delete() { return table_->commit_delete(old_record_); }

RC TrxEvent::rollback_delete() { return table_->rollback_delete(old_record_); }

RC TrxEvent::commit_update() { return RC::SUCCESS; }

RC TrxEvent::rollback_update() { return RC::SUCCESS; }
