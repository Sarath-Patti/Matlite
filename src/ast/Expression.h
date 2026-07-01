#pragma once

#include "lexer/Token.h"

#include <memory>
#include <string>

namespace matlite::ast {

enum class ExpressionKind {
    Binary,
    Literal,
    Identifier,
    Assignment
};

class Expression {
public:
    virtual ~Expression();

    [[nodiscard]] virtual ExpressionKind kind() const noexcept = 0;
};

class BinaryExpression final : public Expression {
public:
    BinaryExpression(
        std::unique_ptr<Expression> left,
        lexer::Token operator_token,
        std::unique_ptr<Expression> right
    );

    [[nodiscard]] ExpressionKind kind() const noexcept override;

    std::unique_ptr<Expression> left;
    lexer::Token operator_token;
    std::unique_ptr<Expression> right;
};

class LiteralExpression final : public Expression {
public:
    explicit LiteralExpression(lexer::Token token);

    [[nodiscard]] ExpressionKind kind() const noexcept override;

    lexer::Token token;
};

class IdentifierExpression final : public Expression {
public:
    explicit IdentifierExpression(lexer::Token token);

    [[nodiscard]] ExpressionKind kind() const noexcept override;

    lexer::Token token;
};

class AssignmentExpression final : public Expression {
public:
    AssignmentExpression(lexer::Token identifier, std::unique_ptr<Expression> value);

    [[nodiscard]] ExpressionKind kind() const noexcept override;

    lexer::Token identifier;
    std::unique_ptr<Expression> value;
};

} // namespace matlite::ast

