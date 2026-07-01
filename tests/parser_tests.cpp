#include "ast/Expression.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include "parser/Parser.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

namespace {

using matlite::ast::AssignmentExpression;
using matlite::ast::BinaryExpression;
using matlite::ast::Expression;
using matlite::ast::ExpressionKind;
using matlite::ast::IdentifierExpression;
using matlite::ast::LiteralExpression;
using matlite::lexer::Lexer;
using matlite::lexer::TokenType;
using matlite::parser::Parser;

std::unique_ptr<Expression> parse_source(const std::string& source)
{
    Lexer lexer(source);
    Parser parser(lexer.tokenize());
    return parser.parse();
}

template <typename ExpressionType>
const ExpressionType* as(const Expression* expression)
{
    return dynamic_cast<const ExpressionType*>(expression);
}

bool fail(const std::string& test_name, const std::string& message)
{
    std::cerr << test_name << ": " << message << '\n';
    return false;
}

bool parses_addition_after_multiplication()
{
    constexpr auto test_name = "parses addition after multiplication";
    const auto expression = parse_source("1 + 2 * 3");
    const auto* root = as<BinaryExpression>(expression.get());

    if (root == nullptr || root->operator_token.type != TokenType::Plus) {
        return fail(test_name, "expected root plus expression");
    }

    const auto* left = as<LiteralExpression>(root->left.get());
    const auto* right = as<BinaryExpression>(root->right.get());

    if (left == nullptr || left->token.lexeme != "1") {
        return fail(test_name, "expected literal 1 on the left");
    }

    if (right == nullptr || right->operator_token.type != TokenType::Multiply) {
        return fail(test_name, "expected multiplication on the right");
    }

    return true;
}

bool parses_parenthesized_expression()
{
    constexpr auto test_name = "parses parenthesized expression";
    const auto expression = parse_source("(1 + 2) * 3");
    const auto* root = as<BinaryExpression>(expression.get());

    if (root == nullptr || root->operator_token.type != TokenType::Multiply) {
        return fail(test_name, "expected root multiply expression");
    }

    const auto* left = as<BinaryExpression>(root->left.get());
    const auto* right = as<LiteralExpression>(root->right.get());

    if (left == nullptr || left->operator_token.type != TokenType::Plus) {
        return fail(test_name, "expected grouped addition on the left");
    }

    if (right == nullptr || right->token.lexeme != "3") {
        return fail(test_name, "expected literal 3 on the right");
    }

    return true;
}

bool parses_right_associative_power()
{
    constexpr auto test_name = "parses right associative power";
    const auto expression = parse_source("2 ^ 3 ^ 4");
    const auto* root = as<BinaryExpression>(expression.get());

    if (root == nullptr || root->operator_token.type != TokenType::Power) {
        return fail(test_name, "expected root power expression");
    }

    const auto* left = as<LiteralExpression>(root->left.get());
    const auto* right = as<BinaryExpression>(root->right.get());

    if (left == nullptr || left->token.lexeme != "2") {
        return fail(test_name, "expected literal 2 on the left");
    }

    if (right == nullptr || right->operator_token.type != TokenType::Power) {
        return fail(test_name, "expected nested power on the right");
    }

    return true;
}

bool parses_right_associative_assignment()
{
    constexpr auto test_name = "parses right associative assignment";
    const auto expression = parse_source("a = b = 42");
    const auto* root = as<AssignmentExpression>(expression.get());

    if (root == nullptr || root->identifier.lexeme != "a") {
        return fail(test_name, "expected assignment to a");
    }

    const auto* nested = as<AssignmentExpression>(root->value.get());
    if (nested == nullptr || nested->identifier.lexeme != "b") {
        return fail(test_name, "expected nested assignment to b");
    }

    const auto* value = as<LiteralExpression>(nested->value.get());
    if (value == nullptr || value->token.lexeme != "42") {
        return fail(test_name, "expected literal 42 as nested value");
    }

    return true;
}

bool parses_identifier()
{
    constexpr auto test_name = "parses identifier";
    const auto expression = parse_source("answer");

    if (expression == nullptr || expression->kind() != ExpressionKind::Identifier) {
        return fail(test_name, "expected identifier expression");
    }

    const auto* identifier = as<IdentifierExpression>(expression.get());
    if (identifier == nullptr || identifier->token.lexeme != "answer") {
        return fail(test_name, "expected identifier named answer");
    }

    return true;
}

bool rejects_incomplete_expression()
{
    constexpr auto test_name = "rejects incomplete expression";
    const auto expression = parse_source("1 +");

    if (expression != nullptr) {
        return fail(test_name, "expected parse failure");
    }

    return true;
}

bool rejects_trailing_tokens()
{
    constexpr auto test_name = "rejects trailing tokens";
    const auto expression = parse_source("1 2");

    if (expression != nullptr) {
        return fail(test_name, "expected parse failure");
    }

    return true;
}

} // namespace

int main()
{
    bool passed = true;

    passed = parses_addition_after_multiplication() && passed;
    passed = parses_parenthesized_expression() && passed;
    passed = parses_right_associative_power() && passed;
    passed = parses_right_associative_assignment() && passed;
    passed = parses_identifier() && passed;
    passed = rejects_incomplete_expression() && passed;
    passed = rejects_trailing_tokens() && passed;

    return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}

