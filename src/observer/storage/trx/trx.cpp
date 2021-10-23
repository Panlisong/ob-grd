#include <atomic>

#include "common/log/log.h"
#include "storage/common/field_meta.h"
#include "storage/common/record_manager.h"
#include "storage/common/table.h"
#include "storage/trx/trx.h"

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
  TrxEvent *trx_event = new TrxEvent(table, type, old_record, new_record);
  trx_events_.push_back(trx_event);
}

RC Trx::commit() {
  RC rc = RC::SUCCESS;
  trx_event_ = trx_events_.front();
  while (trx_event_ != nullptr) {
    switch (trx_event_->get_type()) {
    case TrxEvent::Type::INSERT: {
      rc = trx_event_->commit_insert();
    } break;
    case TrxEvent::Type::DELETE: {
      rc = trx_event_->commit_delete();
    } break;
    case TrxEvent::Type::UPDATE: {
      rc = trx_event_->commit_update();
    } break;
    default: {
    } break;
    };

    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to commit record data, table=%s, rc=%d:%s",
                trx_event_->get_table_name(), rc, strrc(rc));
      rollback();
    }

    trx_event_++;
  }
  return RC::SUCCESS;
}

void Trx::rollback() {
  RC rc = RC::SUCCESS;
  while (trx_event_ != nullptr) {
    switch (trx_event_->get_type()) {
    case TrxEvent::Type::INSERT: {
      rc = trx_event_->rollback_insert();
    } break;
    case TrxEvent::Type::DELETE: {
      rc = trx_event_->rollback_delete();
    } break;
    case TrxEvent::Type::UPDATE: {
      rc = trx_event_->rollback_update();
    } break;
    }

    if (rc != SUCCESS) {
      LOG_PANIC("Failed to rollback, table=%s, rid=%d, rc=%d:%s",
                trx_event_->get_table_name(), 0, rc, strrc(rc));
    }
    trx_event_--;
  }

  trx_events_.clear();
	trx_event_=nullptr;
  trx_id_ = 0;
}

RC TrxEvent::commit_insert() { return table_->commit_insert(new_record_); }

RC TrxEvent::rollback_insert() { return table_->rollback_insert(new_record_); }

RC TrxEvent::commit_delete() { return table_->commit_delete(old_record_); }

RC TrxEvent::rollback_delete() { return table_->rollback_delete(old_record_); }
