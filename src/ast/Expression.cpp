#include "ast/Expression.h"

#include <utility>

namespace matlite::ast {

Expression::~Expression() = default;

BinaryExpression::BinaryExpression(
    std::unique_ptr<Expression> left,
    lexer::Token operator_token,
    std::unique_ptr<Expression> right
)
    : left(std::move(left))
    , operator_token(std::move(operator_token))
    , right(std::move(right))
{
}

ExpressionKind BinaryExpression::kind() const noexcept
{
    return ExpressionKind::Binary;
}

LiteralExpression::LiteralExpression(lexer::Token token)
    : token(std::move(token))
{
}

ExpressionKind LiteralExpression::kind() const noexcept
{
    return ExpressionKind::Literal;
}

IdentifierExpression::IdentifierExpression(lexer::Token token)
    : token(std::move(token))
{
}

ExpressionKind IdentifierExpression::kind() const noexcept
{
    return ExpressionKind::Identifier;
}

AssignmentExpression::AssignmentExpression(lexer::Token identifier, std::unique_ptr<Expression> value)
    : identifier(std::move(identifier))
    , value(std::move(value))
{
}

ExpressionKind AssignmentExpression::kind() const noexcept
{
    return ExpressionKind::Assignment;
}

} // namespace matlite::ast

