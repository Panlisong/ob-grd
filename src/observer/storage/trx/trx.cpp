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

  if (old_record != nullptr) {
    int32_t *ptrx_id = (int32_t *)(old_record->data + trx_field->offset());
    *ptrx_id = DELETED_FLAG_BIT_MASK | trx_id_;
  }
  if (new_record != nullptr) {
    int32_t *ptrx_id = (int32_t *)(new_record->data + trx_field->offset());
    *ptrx_id = trx_id_;
  }
  TrxEvent *trx_event = new TrxEvent(table, type, old_record, new_record);
  trx_events_.push_back(trx_event);
  trx_event_ = trx_events_.begin();
}

RC Trx::commit() {
  RC rc = RC::SUCCESS;
  while (trx_event_ != trx_events_.end()) {
    TrxEvent *trx_event = *trx_event_;
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

    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to commit record data, table=%s, rc=%d:%s",
                trx_event->get_table_name(), rc, strrc(rc));
      rollback();
    }

    trx_event_++;
  }
  return RC::SUCCESS;
}

void Trx::rollback() {
  RC rc = RC::SUCCESS;
  TrxEvent *trx_event;
  while (trx_event_ != trx_events_.begin()) {
    trx_event = *trx_event_;
    switch (trx_event->get_type()) {
    case TrxEvent::Type::INSERT: {
      LOG_INFO("point 3\n");
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
    trx_event_--;
  }
}

RC TrxEvent::commit_insert() { return table_->commit_insert(new_record_); }

RC TrxEvent::rollback_insert() { return table_->rollback_insert(new_record_); }

RC TrxEvent::commit_delete() { return table_->commit_delete(old_record_); }

RC TrxEvent::rollback_delete() { return table_->rollback_delete(old_record_); }

RC TrxEvent::commit_update() { return RC::SUCCESS; }

RC TrxEvent::rollback_update() { return RC::SUCCESS; }
