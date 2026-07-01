#include "evaluator/Evaluator.h"

#include "lexer/Token.h"

#include <cmath>
#include <stdexcept>
#include <string>

namespace matlite::evaluator {

namespace {

using ast::AssignmentExpression;
using ast::BinaryExpression;
using ast::Expression;
using ast::ExpressionKind;
using ast::IdentifierExpression;
using ast::LiteralExpression;
using lexer::TokenType;

const LiteralExpression& as_literal(const Expression& expression)
{
    return static_cast<const LiteralExpression&>(expression);
}

const BinaryExpression& as_binary(const Expression& expression)
{
    return static_cast<const BinaryExpression&>(expression);
}

const IdentifierExpression& as_identifier(const Expression& expression)
{
    return static_cast<const IdentifierExpression&>(expression);
}

const AssignmentExpression& as_assignment(const Expression& expression)
{
    return static_cast<const AssignmentExpression&>(expression);
}

double evaluate_literal(const LiteralExpression& expression)
{
    try {
        return std::stod(expression.token.lexeme);
    } catch (const std::exception&) {
        throw std::runtime_error("Invalid numeric literal: '" + expression.token.lexeme + "'.");
    }
}

double apply_binary_operator(TokenType operator_type, double left, double right)
{
    switch (operator_type) {
    case TokenType::Plus:
        return left + right;
    case TokenType::Minus:
        return left - right;
    case TokenType::Multiply:
        return left * right;
    case TokenType::Divide:
        return left / right;
    case TokenType::Power:
        return std::pow(left, right);
    default:
        throw std::runtime_error("Unsupported binary operator in expression evaluator.");
    }
}

} // namespace

double Evaluator::evaluate(const Expression& expression)
{
    switch (expression.kind()) {
    case ExpressionKind::Literal:
        return evaluate_literal(as_literal(expression));

    case ExpressionKind::Binary: {
        const auto& binary = as_binary(expression);
        if (binary.left == nullptr || binary.right == nullptr) {
            throw std::runtime_error("Invalid binary expression: missing operand.");
        }

        const auto left = evaluate(*binary.left);
        const auto right = evaluate(*binary.right);
        return apply_binary_operator(binary.operator_token.type, left, right);
    }

    case ExpressionKind::Identifier: {
        const auto& identifier = as_identifier(expression);
        throw std::runtime_error("Variables are not yet supported: '" + identifier.token.lexeme + "'.");
    }

    case ExpressionKind::Assignment: {
        const auto& assignment = as_assignment(expression);
        throw std::runtime_error("Variables are not yet supported: assignment to '" + assignment.identifier.lexeme + "'.");
    }
    }

    throw std::runtime_error("Unsupported expression type in evaluator.");
}

} // namespace matlite::evaluator

