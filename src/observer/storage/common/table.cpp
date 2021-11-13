/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/13.
//

#include <algorithm>
#include <limits.h>
#include <list>
#include <string.h>

#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "storage/common/bplus_tree_index.h"
#include "storage/common/condition_filter.h"
#include "storage/common/index.h"
#include "storage/common/meta_util.h"
#include "storage/common/record_manager.h"
#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/trx/trx.h"

Table::Table()
    : data_buffer_pool_(nullptr), file_id_(-1), record_handler_(nullptr) {}

Table::~Table() {
  delete record_handler_;
  record_handler_ = nullptr;

  if (data_buffer_pool_ != nullptr && file_id_ >= 0) {
    data_buffer_pool_->close_file(file_id_);
    data_buffer_pool_ = nullptr;
  }

  LOG_INFO("Table has been closed: %s", name());
}

const char *Table::name() const { return table_meta_.name(); }

const TableMeta &Table::table_meta() const { return table_meta_; }

RC Table::create(const char *path, const char *name, const char *base_dir,
                 int attribute_count, const AttrInfo attributes[]) {

  if (nullptr == name || common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN(
        "Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p",
        name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在

  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (-1 == fd) {
    if (EEXIST == errno) {
      LOG_ERROR(
          "Failed to create table file, it has been created. %s, EEXIST, %s",
          path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path,
              errno, strerror(errno));
    return RC::IOERR;
  }

  close(fd);

  // 创建文件
  if ((rc = table_meta_.init(name, attribute_count, attributes)) !=
      RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc; // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path,
              strerror(errno));
    return RC::IOERR;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  std::string data_file = table_data_file(base_dir, name);
  data_buffer_pool_ = theGlobalDiskBufferPool();
  rc = data_buffer_pool_->create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s",
              data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);

  base_dir_ = base_dir;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::init_record_handler(const char *base_dir) {
  std::string data_file = table_data_file(base_dir, name());
  if (nullptr == data_buffer_pool_) {
    data_buffer_pool_ = theGlobalDiskBufferPool();
  }

  int data_buffer_pool_file_id;
  RC rc = data_buffer_pool_->open_file(data_file.c_str(),
                                       &data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s",
              data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc = record_handler_->init(*data_buffer_pool_, data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  file_id_ = data_buffer_pool_file_id;
  return rc;
}

RC Table::clear() {
  RC rc = RC::SUCCESS;
  std::string table_meta_path = table_meta_file(base_dir_.c_str(), name());
  rc = data_buffer_pool_->close_file(file_id_);
  record_handler_->close();
  delete record_handler_;

  if (remove(table_meta_path.c_str()) != 0) {
    LOG_ERROR("Delete table %s meta failed", name());
    rc = RC::IOERR_DELETE;
  }

  std::string table_data_path = table_data_file(base_dir_.c_str(), name());
  if (remove(table_data_path.c_str()) != 0) {
    LOG_ERROR("Delete table %s data failed", name());
    rc = RC::IOERR_DELETE;
  }

  for (auto index : indexes_) {
    const char *index_name = index->index_meta().name();
    std::string index_path =
        index_data_file(base_dir_.c_str(), name(), index_name);
    if (remove(index_path.c_str()) != 0) {
      LOG_ERROR("Delete table %s index %s error", name(), index_name);
      rc = RC::IOERR_DELETE;
    }
  }
  return rc;
}

RC Table::open(const char *meta_file, const char *base_dir) {
  // 加载元数据文件
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + "/" + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s",
              meta_file, strerror(errno));
    return RC::IOERR;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file);
    return RC::GENERIC_ERROR;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  std::vector<FieldMeta> fields;
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    for (int j = 0; j < index_meta->field_num(); j++) {
      const FieldMeta *field_meta = table_meta_.field(index_meta->field(j));
      if (field_meta == nullptr) {
        LOG_PANIC("Found invalid index meta info which has a non-exists field. "
                  "table=%s, index=%s, field=%s",
                  name(), index_meta->name(), index_meta->field(j));
        return RC::GENERIC_ERROR;
      }
      fields.push_back(*field_meta);
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file =
        index_data_file(base_dir, name(), index_meta->name());

    rc = index->open(index_file.c_str(), *index_meta, fields);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
                name(), index_meta->name(), index_file.c_str(), rc, strrc(rc));
      return rc;
    }
    indexes_.push_back(index);
  }
  return rc;
}

RC Table::insert_records(Trx *trx, int inserted_count, Tuples *tuples) {
  RC rc = RC::SUCCESS;

  for (int i = 0; i < inserted_count; i++) {
    rc = insert_record(trx, &tuples[i]);
    if (rc != RC::SUCCESS) {
      break;
    }
  }

  return rc;
}

RC Table::insert_record(Trx *trx, Tuples *tuple) {
  int value_num = tuple->value_num;
  if (value_num <= 0) {
    // LOG_ERROR("Invalid argument. value num=%d, values=%p", value_num,
    // values);
    return RC::INVALID_ARGUMENT;
  }

  char *record_data;
  RC rc = make_record(value_num, tuple, record_data);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  Record *new_record = new Record();
  new_record->data = record_data;

  for (auto index : indexes_) {
    auto index_meta = index->index_meta();
    if (index_meta.is_unique()) {
      auto index = find_index(index_meta.name());

      // 从record提取索引列
      char value[index->attr_length()];
      memset(value, 0, sizeof value);
      index->get_index_column(new_record->data, value);

      // 判断key是否存在
      auto scanner = index->create_scanner(EQUAL_TO, value);
      RID *rid = new RID();
      rc = scanner->next_entry(rid);
      delete rid;
      if (rc == RC::SUCCESS) {
        LOG_ERROR("Failed to insert duplicate key for index %s",
                  index_meta.name());
        scanner->destroy();
        return RC::RECORD_DUPLICATE_KEY;
      }
      scanner->destroy();
    }
  }

  // record.valid = true;
  InsertTrxEvent *event = new InsertTrxEvent(this, new_record);
  trx->pending(event);

  return RC::SUCCESS;
}

RC Table::commit_insert(Record *new_record) {
  if (new_record->data == nullptr) {
    LOG_INFO("no data\n");
  }

  RC rc = record_handler_->insert_record(
      new_record->data, table_meta_.record_size(), &new_record->rid);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Commit insert failed. table name=%s, rc=%d:%s",
              table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  return insert_entry_of_indexes(new_record);
}

RC Table::insert_entry_of_indexes(const Record *new_record) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(new_record->data, &new_record->rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::rollback_insert(Record *new_record) {
  RC rc = delete_entry_of_indexes(new_record->data, new_record->rid, false);
  if (rc == RC::SCHEMA_INDEX_NOT_EXIST) {
    rc = RC::SUCCESS;
  }
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return record_handler_->delete_record(&new_record->rid);
}

RC Table::make_record(int value_num, Tuples *tuple, char *&record_out) {
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    Value *value = tuple->values[value_num - 1 - i];
    if (field->type() == ATTR_TEXT && value->type == CHARS) {
      // insert text.
      continue;
    }
    if (value->type == ATTR_NULL) {
      if (field->nullable() == false) {
        LOG_ERROR("Invalid value type.field name=%s, not null but given=null",
                  field->name());
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      } else {
        continue;
      }
    }
    if (field->type() != value->type) {
      LOG_ERROR("Invalid value type. field name=%s, type=%d, nullable=%d but "
                "given=%d",
                field->name(), field->type(), field->nullable(), value->type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  char *record = new char[record_size];
  memset(record, 0, record_size);
  RC rc = RC::SUCCESS;

  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    Value *value = tuple->values[value_num - 1 - i];
    if (value->type == ATTR_NULL) {
      // bit i means value[i] is null.
      int null_field_offset = table_meta_.null_field()->offset();
      int32_t *null_field = (int32_t *)(record + null_field_offset);
      *null_field |= (1 << i);
    } else {
      if (field->type() == ATTR_TEXT && value->type == CHARS) {
        rc = make_text(field, value, record);
        if (rc != RC::SUCCESS) {
          break;
        }
      } else {
        memcpy(record + field->offset(), value->data, field->len());
      }
    }
  }

  record_out = record;
  return rc;
}
/**
 * 为了不把Record暴露出去，封装一下
 */
class RecordReaderScanAdapter {
public:
  explicit RecordReaderScanAdapter(void (*record_reader)(const char *data,
                                                         void *context),
                                   void *context)
      : record_reader_(record_reader), context_(context) {}

  void consume(const Record *record) { record_reader_(record->data, context_); }

private:
  void (*record_reader_)(const char *, void *);
  void *context_;
};

static RC scan_record_reader_adapter(Record *record, void *context) {
  RecordReaderScanAdapter &adapter = *(RecordReaderScanAdapter *)context;
  adapter.consume(record);
  return RC::SUCCESS;
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit,
                      void *context,
                      void (*record_reader)(const char *data, void *context)) {
  RecordReaderScanAdapter adapter(record_reader, context);
  return scan_record(trx, filter, limit, (void *)&adapter,
                     scan_record_reader_adapter);
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit,
                      void *context,
                      RC (*record_reader)(Record *record, void *context)) {
  if (0 == limit) {
    return RC::SUCCESS;
  }

  if (limit < 0) {
    limit = INT_MAX;
  }

  IndexScanner *index_scanner = find_index_for_scan(filter);
  if (index_scanner != nullptr) {
    return scan_record_by_index(trx, index_scanner, filter, limit, context,
                                record_reader);
  }

  RC rc = RC::SUCCESS;
  RecordFileScanner scanner;
  rc = scanner.open_scan(*data_buffer_pool_, file_id_, filter);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open scanner. file id=%d. rc=%d:%s", file_id_, rc,
              strrc(rc));
    return rc;
  }

  int record_count = 0;
  Record record;
  rc = scanner.get_first_record(&record);
  while (rc == RC::SUCCESS && record_count < limit) {
    rc = record_reader(&record, context);
    if (rc != RC::SUCCESS) {
      break;
    }
    record_count++;
    rc = scanner.get_next_record(&record);
  }

  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_ERROR("Failed to scan record. file id=%d, rc=%d:%s", file_id_, rc,
              strrc(rc));
  }
  scanner.close_scan();
  return rc;
}

RC Table::scan_record_by_index(Trx *trx, IndexScanner *scanner,
                               ConditionFilter *filter, int limit,
                               void *context,
                               RC (*record_reader)(Record *, void *)) {
  RC rc = RC::SUCCESS;
  RID rid;
  Record record;
  int record_count = 0;
  while (record_count < limit) {
    rc = scanner->next_entry(&rid);
    if (rc != RC::SUCCESS) {
      if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
        break;
      }
      LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
      break;
    }

    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s", rid.page_num,
                rid.slot_num, rc, strrc(rc));
      break;
    }

    if (filter == nullptr || filter->filter(record, rc)) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        LOG_TRACE("Record reader break the table scanning. rc=%d:%s", rc,
                  strrc(rc));
        break;
      }
    }

    record_count++;
  }

  scanner->destroy();
  return rc;
}

class IndexInserter {
public:
  explicit IndexInserter(Index *index) : index_(index) {}

  RC insert_index(const Record *record) {
    auto index_meta = index_->index_meta();
    if (index_meta.is_unique()) {
      // 构造search key
      char values[index_->attr_length()];
      memset(values, 0, sizeof values);
      index_->get_index_column(record->data, values);
      // 判断插入索引的search key是否存在
      auto scanner = index_->create_scanner(EQUAL_TO, values);
      RID *rid = new RID();
      RC rc = scanner->next_entry(rid);
      delete rid;
      if (rc == RC::SUCCESS) {
        LOG_ERROR("Failed to insert duplicate key for index %s",
                  index_->index_meta().name());
        scanner->destroy();
        return RC::RECORD_DUPLICATE_KEY;
      }
      scanner->destroy();
    }
    return index_->insert_entry(record->data, &record->rid);
  }

private:
  Index *index_;
};

static RC insert_index_record_reader_adapter(Record *record, void *context) {
  IndexInserter &inserter = *(IndexInserter *)context;
  return inserter.insert_index(record);
}

RC Table::create_index(Trx *trx, const char *index_name, bool unique,
                       std::vector<std::string> &attrs) {
  if (index_name == nullptr || common::is_blank(index_name)) {
    return RC::INVALID_ARGUMENT;
  }

  for (size_t i = 0; i < attrs.size(); i++) {
    if (attrs[i].empty() || common::is_blank(attrs[i].c_str())) {
      return RC::INVALID_ARGUMENT;
    }
  }

  // 1. 是否存在同名索引
  if (table_meta_.index(index_name) != nullptr) {
    return RC::SCHEMA_INDEX_EXIST;
  }

  // 2. 建立索引字段是否存在
  std::vector<FieldMeta> fields;
  for (int i = 0; i < static_cast<int>(attrs.size()); i++) {
    const FieldMeta *field_meta = table_meta_.field(attrs[i].c_str());
    if (!field_meta) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.push_back(*field_meta);
  }

  // 3. 相同字段索引是否已存在
  // 不可使用find_index_by_field
  // 只有某个索引的field完全匹配才认为已创建
  for (int i = 0; i < table_meta_.index_num(); i++) {
    auto index_meta = table_meta_.index(i);
    if (index_meta->field_num() != static_cast<int>(attrs.size())) {
      // 建立的多列索引和当前遍历到的索引列数不同，它们一定不同
      break;
    }
    // 严格按照顺序匹配
    bool error = true;
    for (int j = 0; j < index_meta->field_num(); j++) {
      if (strcmp(index_meta->field(j), attrs[j].c_str()) != 0) {
        error = false;
        break;
      }
    }
    if (error) {
      return RC::SCHEMA_INDEX_EXIST;
    }
  }

  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, attrs, unique);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file =
      index_data_file(base_dir_.c_str(), name(), index_name);
  rc = index->create(index_file.c_str(), new_index_meta, fields);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s",
              index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  IndexInserter index_inserter(index);
  rc = scan_record(trx, nullptr, -1, &index_inserter,
                   insert_index_record_reader_adapter);
  if (rc != RC::SUCCESS) {
    // rollback
    delete index;
    remove(index_file.c_str());
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s",
              name(), rc, strrc(rc));
    return rc;
  }
  indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name,
              name(), rc, strrc(rc));
    return rc;
  }
  // 创建元数据临时文件
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file,
          std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s",
              tmp_file.c_str(), strerror(errno));
    return RC::IOERR; // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s",
              tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) "
              "while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno,
              strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("add a new index (%s) on the table (%s)", index_name, name());

  return rc;
}

class RecordUpdater {
public:
  RecordUpdater(Table &table, Trx *trx) : table_(table), trx_(trx) {}
  RC update_record(Record *old_record) {
    RC rc = RC::SUCCESS;
    // 拷贝old record和new record
    Record *old_rec = new Record();
    old_rec->rid = old_record->rid;
    old_rec->data = new char[table_.table_meta_.record_size()];

    memcpy(old_rec->data, old_record->data, table_.table_meta_.record_size());

    // 检查unique完整性约束
    for (auto index : table_.indexes_) {
      auto index_meta = index->index_meta();
      if (index_meta.is_unique()) {
        // 判断更新字段是否在索引字段之中
        bool exist = false;
        for (int i = 0; i < index_meta.field_num(); i++) {
          if (strcmp(index_meta.field(i), field_meta_.name()) == 0) {
            exist = true;
            break;
          }
        }
        if (exist) {
          // 从新record中提取索引字段(key)
          char value[index->attr_length()];
          memset(value, 0, sizeof value);
          index->get_index_column(old_record->data, value);

          // 判断插入B+树的key是否存在
          auto scanner = index->create_scanner(EQUAL_TO, value);
          RID *rid = new RID();
          rc = scanner->next_entry(rid);
          delete rid;
          if (rc == RC::SUCCESS) {
            rc = RC::RECORD_DUPLICATE_KEY;
            LOG_ERROR("Failed to update duplicate key for index %s",
                      index_meta.name());
            scanner->destroy();
            return rc;
          }
          scanner->destroy();
        }
      }
    }

    UpdateTrxEvent *event = new UpdateTrxEvent(
        &table_, old_rec, value_, offset_, len_, is_text_, field_meta_);
    trx_->pending(event);
    updated_count_++;

    return RC::SUCCESS;
  }

  void set_update_info(const Value *v, int offset, int len, bool is_text,
                       FieldMeta field_meta) {
    value_ = v;
    offset_ = offset;
    len_ = len;
    is_text_ = is_text;
    field_meta_ = field_meta;
  }

  int updated_count() const { return updated_count_; }

private:
  Table &table_;
  Trx *trx_;
  const Value *value_;
  int offset_;
  int len_;
  bool is_text_;
  FieldMeta field_meta_;
  int updated_count_ = 0;
};

static RC record_reader_update_adapter(Record *record, void *context) {
  RecordUpdater &record_updater = *(RecordUpdater *)context;
  return record_updater.update_record(record);
}

RC Table::update_records(Trx *trx, const char *attribute_name,
                         const Value *value, int condition_num,
                         const ConditionList *conditions, int *updated_count) {
  RC rc = RC::SUCCESS;
  // 进入这里说明更新Table一定存在
  // 1. 生成ConditionFilter
  CompositeConditionFilter filter = CompositeConditionFilter();
  rc = filter.init(trx, *this, conditions, condition_num);
  if (rc != RC::SUCCESS)
    return rc;

  // 2. 创建Updater（获取Attr在Record中的实际偏移和大小）
  // (1) 检查更新字段是否存在
  const FieldMeta *field_meta = table_meta_.field(attribute_name);
  if (field_meta == nullptr) {
    LOG_WARN("No such field. %s.%s", name(), attribute_name);
    return RC::SCHEMA_FIELD_MISSING;
  }
  // (2) 检查类型是否匹配
  // 目前实现类型不同则报错
  if (field_meta->type() == ATTR_TEXT && value->type == CHARS) {
  } else if (field_meta->type() != value->type &&
             field_meta->nullable() == false) {
    LOG_WARN("Type dismatching.");
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  RecordUpdater updater(*this, trx);
  updater.set_update_info(value, field_meta->offset(), field_meta->len(),
                          field_meta->type() == ATTR_TEXT, *field_meta);
  rc = scan_record(trx, &filter, -1, &updater, record_reader_update_adapter);
  if (updated_count != nullptr) {
    *updated_count = updater.updated_count();
  }
  return rc;
}

RC Table::commit_update(Record *record, bool new_null, char *new_value,
                        int offset, int len, bool is_text) {
  if (new_null) {
    int column = find_column_by_offset(offset);
    int32_t *null_field = (int32_t *)(record + null_field_offset());
    *null_field |= (1 << column);
  } else {
    if (is_text) {
      update_text(record, new_value, offset);
    } else {
      memcpy(record->data + offset, new_value, len);
    }
  }
  // RC rc = update_entry_of_indexes(old_record->data, old_record->rid);
  RC rc = RC::SUCCESS;
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to update indexes of record(rid=%d.%d). rc=%d:%s",
              record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
    return rc;
  }
  return record_handler_->update_record(record);
}

RC Table::rollback_update(Record *record, bool old_null, char *old_value,
                          int offset, int len) {
  int column = table_meta_.find_column_by_offset(offset);
  int null_field_offset = table_meta_.null_field()->offset();
  int32_t *null_field = (int32_t *)(record + null_field_offset);
  if (old_null) {
    *null_field &= (1 << column);
  } else {
    *null_field &= 0xFFFFFFFF - (1 << column);
    memcpy(record->data + offset, old_value, len);
  }
  // RC rc = update_entry_of_indexes(old_record->data, old_record->rid);
  RC rc = RC::SUCCESS;
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to rollback for updating indexes of record(rid=%d.%d). "
              "rc=%d:%s",
              record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
    return rc;
  }
  return record_handler_->update_record(record);
}

RC Table::update_entry_of_indexes(const char *old_rec, const char *new_rec,
                                  const RID &rid) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    // Update某个索引字段可以看作：先删除再插入
    rc = index->delete_entry(old_rec, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
    rc = index->insert_entry(new_rec, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}
class RecordDeleter {
public:
  RecordDeleter(Table &table, Trx *trx) : table_(table), trx_(trx) {}

  RC delete_record(Record *old_record) {
    Record *record = new Record();
    record->rid = old_record->rid;
    record->data = new char[table_.table_meta_.record_size()];

    memcpy(record->data, old_record->data, table_.table_meta_.record_size());
    DeleteTrxEvent *event = new DeleteTrxEvent(&table_, record);
    trx_->pending(event);

    deleted_count_++;

    return RC::SUCCESS;
  }

  int deleted_count() const { return deleted_count_; }

private:
  Table &table_;
  Trx *trx_;
  int deleted_count_ = 0;
};

static RC record_reader_delete_adapter(Record *record, void *context) {
  RecordDeleter &record_deleter = *(RecordDeleter *)context;
  return record_deleter.delete_record(record);
}

RC Table::delete_records(Trx *trx, ConditionFilter *filter,
                         int *deleted_count) {
  RecordDeleter deleter(*this, trx);
  RC rc = scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
  if (deleted_count != nullptr) {
    *deleted_count = deleter.deleted_count();
  }
  return rc;
}

RC Table::commit_delete(Record *old_record) {
  RC rc = delete_entry_of_indexes(old_record->data, old_record->rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d). rc=%d:%s",
              old_record->rid.page_num, old_record->rid.slot_num, rc,
              strrc(rc));
    return rc;
  }

  return record_handler_->delete_record(&old_record->rid);
}

RC Table::rollback_delete(Record *old_record) {
  RC rc = insert_entry_of_indexes(old_record);
  if (rc == RC::SCHEMA_INDEX_EXIST) {
    rc = RC::SUCCESS;
  }
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return record_handler_->insert_record(
      old_record->data, table_meta_.record_size(), &old_record->rid);
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid,
                                  bool error_on_not_exists) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const {
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}

IndexScanner *Table::find_index_for_scan(const DefaultConditionFilter &filter) {
  // TODO: find_index_for_scan
  // const ConDesc *field_cond_desc = nullptr;
  // const ConDesc *value_cond_desc = nullptr;
  // if (filter.left().is_attr && !filter.right().is_attr) {
  //   field_cond_desc = &filter.left();
  //   value_cond_desc = &filter.right();
  // } else if (filter.right().is_attr && !filter.left().is_attr) {
  //   field_cond_desc = &filter.right();
  //   value_cond_desc = &filter.left();
  // }
  // if (field_cond_desc == nullptr || value_cond_desc == nullptr) {
  //   return nullptr;
  // }

  // const FieldMeta *field_meta =
  //     table_meta_.find_field_by_offset(field_cond_desc->attr_offset);
  // if (nullptr == field_meta) {
  //   LOG_PANIC("Cannot find field by offset %d. table=%s",
  //             field_cond_desc->attr_offset, name());
  //   return nullptr;
  // }

  // const IndexMeta *index_meta =
  //     table_meta_.find_index_by_field(field_meta->name());
  // if (nullptr == index_meta) {
  //   return nullptr;
  // }

  // Index *index = find_index(index_meta->name());
  // if (nullptr == index) {
  //   return nullptr;
  // }

  // return index->create_scanner(filter.comp_op(),
  //                              (const char *)value_cond_desc->value);
  return nullptr;
}

// TODO: 按照多列索引找最优的index
IndexScanner *Table::find_index_for_scan(const ConditionFilter *filter) {
  if (nullptr == filter) {
    return nullptr;
  }

  // remove dynamic_cast
  const DefaultConditionFilter *default_condition_filter =
      dynamic_cast<const DefaultConditionFilter *>(filter);
  if (default_condition_filter != nullptr) {
    return find_index_for_scan(*default_condition_filter);
  }

  const CompositeConditionFilter *composite_condition_filter =
      dynamic_cast<const CompositeConditionFilter *>(filter);
  if (composite_condition_filter != nullptr) {
    int filter_num = composite_condition_filter->filter_num();
    for (int i = 0; i < filter_num; i++) {
      IndexScanner *scanner =
          find_index_for_scan(&composite_condition_filter->filter(i));
      if (scanner != nullptr) {
        return scanner; // 可以找到一个最优的，比如比较符号是=
      }
    }
  }
  return nullptr;
}

RC Table::sync() {
  RC rc = data_buffer_pool_->flush_all_pages(file_id_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to flush table's data pages. table=%s, rc=%d:%s", name(),
              rc, strrc(rc));
    return rc;
  }

  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
                name(), index->index_meta().name(), rc, strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}

int Table::find_column_by_offset(int offset) {
  return table_meta_.find_column_by_offset(offset);
}

void Table::select_text(char *data, int page_id) {
  record_handler_->select_text(data, page_id);
}

RC Table::make_text(const FieldMeta *field, Value *value, char *record) {
  int page_id;
  int remain_len = 4;
  RC rc = record_handler_->insert_text((char *)(value->data) + remain_len,
                                       &page_id, value->len - remain_len);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  // text in record:
  // | text (first 4 bytes) | page_id (the page contains remain 4092
  // bytes) |
  if (value->len < remain_len) {
    memcpy(record + field->offset(), value->data, value->len);
  } else {
    memcpy(record + field->offset(), value->data, remain_len);
  }

  memcpy(record + field->offset() + remain_len, &page_id,
         field->len() - remain_len);

  return RC::SUCCESS;
}

RC Table::delete_text(Record *old_record) {
  int page_id;
  int remain_len = 4;
  char *s = new char[5];
  RC rc = RC::SUCCESS;

  for (int i = 2; i < table_meta().field_num(); i++) {
    const FieldMeta *field = table_meta_.field(i);
    if (field->type() != ATTR_TEXT) {
      continue;
    }
    memcpy(s, old_record + field->offset(), remain_len);
    if (s[remain_len - 1] == 0) {
      continue;
    }
    page_id =
        (*(int *)(old_record + field->offset() + remain_len)) & 0x7FFFFFFF;
    rc = record_handler_->delete_text(page_id);
    if (rc != RC::SUCCESS) {
      break;
    }
  }

  delete[] s;

  return rc;
}

RC Table::update_text(Record *record, char *new_value, int offset) {
  int page_id = 0;
  int remain_len = 4;
  char *s = new char[5];
  RC rc = RC::SUCCESS;

  memcpy(s, record->data + offset, remain_len);
  if (s[remain_len - 1] != 0) {
    page_id = *(int *)(record->data + offset + remain_len);
    rc = record_handler_->delete_text(page_id);
    if (rc != RC::SUCCESS) {
      delete[] s;
      return rc;
    }
  }
  page_id = *(int *)(record->data + offset + remain_len);

  int field_len = 8;
  int new_len = strlen(new_value);
  memset(record->data + offset, 0, field_len);

  if (new_len < remain_len) {
    memcpy(record->data + offset, new_value, new_len);
    delete[] s;
    return RC::SUCCESS;
  }

  memcpy(record->data + offset, new_value, remain_len);
  rc = record_handler_->insert_text(new_value + remain_len, &page_id,
                                    new_len - remain_len);
  memcpy(record->data + offset + remain_len, &page_id, field_len - remain_len);

  delete[] s;
  return rc;
}
