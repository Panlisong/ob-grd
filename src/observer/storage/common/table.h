/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/12.
//

#ifndef __OBSERVER_STORAGE_COMMON_TABLE_H__
#define __OBSERVER_STORAGE_COMMON_TABLE_H__

#include "common/log/log.h"
#include "storage/common/record_manager.h"
#include "storage/common/table_meta.h"

class DiskBufferPool;
class RecordFileHandler;
class ConditionFilter;
class DefaultConditionFilter;
struct Record;
struct RID;
class Index;
class IndexScanner;
class RecordDeleter;
class Trx;

class Table {
public:
  Table();
  ~Table();

  const char *name() const;

  const TableMeta &table_meta() const;

  /**
   * 创建一个表
   * @param path 元数据保存的文件(完整路径)
   * @param name 表名
   * @param base_dir 表数据存放的路径
   * @param attribute_count 字段个数
   * @param attributes 字段
   */
  RC create(const char *path, const char *name, const char *base_dir,
            int attribute_count, const AttrInfo attributes[]);
  RC clear();

private:
  RC init_record_handler(const char *base_dir);

public:
  /**
   * 打开一个表
   * @param meta_file 保存表元数据的文件完整路径
   * @param base_dir 表所在的文件夹，表记录数据文件、索引数据文件存放位置
   */
  RC open(const char *meta_file, const char *base_dir);

  RC scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context,
                 void (*record_reader)(const char *data, void *context));

  RC create_index(Trx *trx, const char *index_name, bool unique,
                  std::vector<std::string> &attrs);

public:
  RC insert_records(Trx *trx, int inserted_count, Tuples *tuples);
  RC commit_insert(Record *new_record);
  RC rollback_insert(Record *new_record);

  RC delete_records(Trx *trx, ConditionFilter *filter, int *deleted_count);
  RC commit_delete(Record *old_record);
  RC rollback_delete(Record *old_record);

  RC update_records(Trx *trx, const char *attribute_name, const Value *value,
                    int condition_num, const ConditionList *conditions,
                    int *updated_count);
  RC commit_update(Record *record, bool new_null, char *new_value, int offset,
                   int len, bool is_text);
  RC rollback_update(Record *record, bool old_null, char *old_value, int offset,
                     int len);

  int find_column_by_offset(int offset);
  static int null_field_offset() { return TableMeta::null_field_offset(); }
  static bool record_data_is_null(const Record &rec, int column) {
    int32_t *null_field = (int32_t *)(rec.data + null_field_offset());
    return (((*null_field) & (1 << column)) != 0);
  }

  void select_text(char *data, int page_id);

private:
  RC insert_record(Trx *trx, Tuples *tuple);

public:
  RC sync();

private:
  RC scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context,
                 RC (*record_reader)(Record *record, void *context));
  RC scan_record_by_index(Trx *trx, IndexScanner *scanner,
                          ConditionFilter *filter, int limit, void *context,
                          RC (*record_reader)(Record *record, void *context));

  IndexScanner *find_index_for_scan(const ConditionFilter *filter);
  IndexScanner *find_index_for_scan(const DefaultConditionFilter &filter);

private:
  RC insert_record(Trx *trx, Record *record);
  RC delete_record(Trx *trx, Record *record);

private:
  friend class RecordUpdater;
  friend class RecordDeleter;

  RC insert_entry_of_indexes(const Record *new_record);
  RC delete_entry_of_indexes(const char *record, const RID &rid,
                             bool error_on_not_exists);
  RC update_entry_of_indexes(const char *old_rec, const char *new_rec,
                             const RID &rid);

private:
  RC make_record(int value_num, Tuples *tuple, char *&record_out);
  RC make_text(const FieldMeta *field, Value *value, char *record);
  RC delete_text(Record *old_record);
  RC update_text(Record *record, char *new_value, int offset);

private:
  Index *find_index(const char *index_name) const;

private:
  std::string base_dir_;
  TableMeta table_meta_;
  DiskBufferPool *data_buffer_pool_; /// 数据文件关联的buffer pool
  int file_id_;
  RecordFileHandler *record_handler_; /// 记录操作
  std::vector<Index *> indexes_;
};

#endif // __OBSERVER_STORAGE_COMMON_TABLE_H__
