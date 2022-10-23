//
// Created by JinHai on 2022/9/12.
//

#pragma once

#include "table_ref.h"
#include "common/types.h"

namespace infinity {

class BindContext;

class JoinTableRef: public TableRef {
public:
    explicit JoinTableRef(std::string alias) : TableRef(TableRefType::kJoin, std::move(alias)) {}

    std::shared_ptr<BindContext> left_bind_context_;
    std::shared_ptr<BindContext> right_bind_context_;

    std::shared_ptr<TableRef> left_table_ref_;
    std::shared_ptr<TableRef> right_table_ref_;

    // Condition ???
    std::vector<std::shared_ptr<BaseExpression>> on_conditions_;

    // Join Type ???
    JoinType join_type_;
};

}