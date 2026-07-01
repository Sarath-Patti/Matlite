#include "parser/Parser.h"

#include <utility>

namespace matlite::parser {

namespace {

using lexer::TokenType;

bool is_addition_operator(TokenType type)
{
    return type == TokenType::Plus || type == TokenType::Minus;
}

bool is_multiplication_operator(TokenType type)
{
    return type == TokenType::Multiply || type == TokenType::Divide;
}

bool is_literal(TokenType type)
{
    return type == TokenType::Integer || type == TokenType::Float;
}

} // namespace

Parser::Parser(std::vector<lexer::Token> tokens)
    : tokens_(std::move(tokens))
{
    if (tokens_.empty() || tokens_.back().type != TokenType::EndOfFile) {
        tokens_.emplace_back(TokenType::EndOfFile, "", 1, 1);
    }
}

std::unique_ptr<ast::Expression> Parser::parse()
{
    auto expression = parse_assignment();

    if (!expression || !is_at_end()) {
        return nullptr;
    }

    return expression;
}

std::unique_ptr<ast::Expression> Parser::parse_assignment()
{
    if (check(TokenType::Identifier) && check_next(TokenType::Assign)) {
        const auto identifier = advance();
        advance();

        auto value = parse_assignment();
        if (!value) {
            return nullptr;
        }

        return std::make_unique<ast::AssignmentExpression>(identifier, std::move(value));
    }

    return parse_addition();
}

std::unique_ptr<ast::Expression> Parser::parse_addition()
{
    auto expression = parse_multiplication();
    if (!expression) {
        return nullptr;
    }

    while (!is_at_end() && is_addition_operator(current().type)) {
        const auto operator_token = advance();
        auto right = parse_multiplication();
        if (!right) {
            return nullptr;
        }

        expression = std::make_unique<ast::BinaryExpression>(
            std::move(expression),
            operator_token,
            std::move(right)
        );
    }

    return expression;
}

std::unique_ptr<ast::Expression> Parser::parse_multiplication()
{
    auto expression = parse_power();
    if (!expression) {
        return nullptr;
    }

    while (!is_at_end() && is_multiplication_operator(current().type)) {
        const auto operator_token = advance();
        auto right = parse_power();
        if (!right) {
            return nullptr;
        }

        expression = std::make_unique<ast::BinaryExpression>(
            std::move(expression),
            operator_token,
            std::move(right)
        );
    }

    return expression;
}

std::unique_ptr<ast::Expression> Parser::parse_power()
{
    auto expression = parse_primary();
    if (!expression) {
        return nullptr;
    }

    if (match(TokenType::Power)) {
        const auto operator_token = previous();
        auto right = parse_power();
        if (!right) {
            return nullptr;
        }

        return std::make_unique<ast::BinaryExpression>(
            std::move(expression),
            operator_token,
            std::move(right)
        );
    }

    return expression;
}

std::unique_ptr<ast::Expression> Parser::parse_primary()
{
    if (is_literal(current().type)) {
        return std::make_unique<ast::LiteralExpression>(advance());
    }

    if (match(TokenType::Identifier)) {
        return std::make_unique<ast::IdentifierExpression>(previous());
    }

    if (match(TokenType::LeftParen)) {
        auto expression = parse_assignment();
        if (!expression || !match(TokenType::RightParen)) {
            return nullptr;
        }

        return expression;
    }

    return nullptr;
}

bool Parser::is_at_end() const noexcept
{
    return current().type == TokenType::EndOfFile;
}

bool Parser::check(TokenType type) const noexcept
{
    return current().type == type;
}

bool Parser::check_next(TokenType type) const noexcept
{
    const auto next = current_ + 1;
    return next < tokens_.size() && tokens_[next].type == type;
}

const lexer::Token& Parser::current() const noexcept
{
    return current_ < tokens_.size() ? tokens_[current_] : tokens_.back();
}

const lexer::Token& Parser::previous() const noexcept
{
    return tokens_[current_ - 1];
}

bool Parser::match(TokenType type) noexcept
{
    if (!check(type)) {
        return false;
    }

    advance();
    return true;
}

const lexer::Token& Parser::advance() noexcept
{
    if (!is_at_end()) {
        ++current_;
    }

    return previous();
}

} // namespace matlite::parser
