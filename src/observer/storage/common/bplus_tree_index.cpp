/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/common/bplus_tree_index.h"
#include "common/log/log.h"

BplusTreeIndex::~BplusTreeIndex() noexcept { close(); }

RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta,
                          const std::vector<FieldMeta> &field_metas) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }

  RC rc = Index::init(index_meta, field_metas);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  AttrType types[field_metas.size()];
  int lens[field_metas.size()];
  attr_length_ = 0;
  for (size_t i = 0; i < field_metas.size(); i++) {
    types[i] = field_metas.at(i).type();
    lens[i] = field_metas.at(i).len();
    attr_length_ += lens[i];
  }
  rc = index_handler_.create(file_name, types, lens, field_metas.size(),
                             attr_length_);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta,
                        const std::vector<FieldMeta> &field_metas) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  RC rc = Index::init(index_meta, field_metas);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = index_handler_.open(file_name);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::close() {
  if (inited_) {
    index_handler_.close();
    inited_ = false;
  }
  return RC::SUCCESS;
}

void BplusTreeIndex::get_index_column(const char *record, char *values) {
  int next = 0;
  for (size_t i = 0; i < field_metas_.size(); i++) {
    auto field = field_metas_[i];
    memcpy(values + next, record + field.offset(), field.len());
    next += field.len();
  }
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid) {
  // 从record中提取索引列
  char values[attr_length_];
  memset(values, 0, sizeof values);
  get_index_column(record, values);
  return index_handler_.insert_entry(values, rid);
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid) {
  // 从record中提取索引列
  char values[attr_length_];
  memset(values, 0, sizeof values);
  get_index_column(record, values);
  return index_handler_.delete_entry(values, rid);
}

IndexScanner *BplusTreeIndex::create_scanner(CompOp comp_op,
                                             const char *value) {
  BplusTreeScanner *bplus_tree_scanner = new BplusTreeScanner(index_handler_);
  RC rc = bplus_tree_scanner->open(comp_op, value);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete bplus_tree_scanner;
    return nullptr;
  }

  BplusTreeIndexScanner *index_scanner =
      new BplusTreeIndexScanner(bplus_tree_scanner);
  return index_scanner;
}

RC BplusTreeIndex::sync() { return index_handler_.sync(); }

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeScanner *tree_scanner)
    : tree_scanner_(tree_scanner) {}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept {
  tree_scanner_->close();
  delete tree_scanner_;
}

RC BplusTreeIndexScanner::next_entry(RID *rid) {
  return tree_scanner_->next_entry(rid);
}

RC BplusTreeIndexScanner::destroy() {
  delete this;
  return RC::SUCCESS;
}