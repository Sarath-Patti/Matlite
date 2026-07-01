#pragma once

#include "ast/Expression.h"

namespace matlite::evaluator {

class Evaluator {
public:
    double evaluate(const ast::Expression& expression);
};

} // namespace matlite::evaluator

