#pragma once

#include "visitor.h"
#include <functional>

struct calculator : visitor {
    std::any visit_num(num_node *ctx) override { return ctx->number; }

    std::any visit_add(add_node *ctx) override {
        return evaluate(ctx->lnode, ctx->rnode, std::plus<>{});
    }
    std::any visit_sub(sub_node *ctx) override {
        return evaluate(ctx->lnode, ctx->rnode, std::minus<>{});
    }
    std::any visit_mul(mul_node *ctx) override {
        return evaluate(ctx->lnode, ctx->rnode, std::multiplies<>{});
    }
    std::any visit_div(div_node *ctx) override {
        return evaluate(ctx->lnode, ctx->rnode, std::divides<>{});
    }
    ~calculator() override = default;

private:
    template <class Operation>
    std::any evaluate(node *left, node *right, Operation operation) {
        const std::any lhs = visit(left);
        const std::any rhs = visit(right);
        // Every leaf in a tree has the same numeric type.
        if (const auto *value = std::any_cast<long long>(&lhs)) {
            return operation(*value, std::any_cast<long long>(rhs));
        }
        return operation(std::any_cast<double>(lhs), std::any_cast<double>(rhs));
    }
};
