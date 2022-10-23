//
// Created by JinHai on 2022/7/26.
//

#include "optimizer.h"

namespace infinity {

void
Optimizer::AddRule(std::unique_ptr<OptimizerRule> rule) {
    rules_.emplace_back(std::move(rule));
}

std::shared_ptr<LogicalNode>
Optimizer::optimize(const std::shared_ptr<LogicalNode>& unoptimized_plan) {
    for(const auto& rule : rules_) {
        rule->ApplyToPlan(query_context_ptr_, unoptimized_plan);
    }
    return unoptimized_plan;
}

}