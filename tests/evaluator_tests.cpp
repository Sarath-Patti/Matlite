#include "ast/Expression.h"
#include "evaluator/Evaluator.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include "parser/Parser.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace {

using matlite::ast::AssignmentExpression;
using matlite::ast::Expression;
using matlite::ast::IdentifierExpression;
using matlite::evaluator::Evaluator;
using matlite::lexer::Lexer;
using matlite::lexer::Token;
using matlite::lexer::TokenType;
using matlite::parser::Parser;

std::unique_ptr<Expression> parse_source(const std::string& source)
{
    Lexer lexer(source);
    Parser parser(lexer.tokenize());
    return parser.parse();
}

bool fail(const std::string& test_name, const std::string& message)
{
    std::cerr << test_name << ": " << message << '\n';
    return false;
}

bool nearly_equal(double left, double right)
{
    return std::fabs(left - right) < 0.000001;
}

bool expects_value(const std::string& source, double expected)
{
    const auto expression = parse_source(source);
    if (expression == nullptr) {
        return fail(source, "parser returned no expression");
    }

    Evaluator evaluator;
    const auto actual = evaluator.evaluate(*expression);

    if (!nearly_equal(actual, expected)) {
        return fail(source, "expected " + std::to_string(expected) + ", got " + std::to_string(actual));
    }

    return true;
}

bool throws_for_identifier()
{
    constexpr auto test_name = "identifier expression";
    const auto identifier = IdentifierExpression(Token(TokenType::Identifier, "x", 1, 1));

    Evaluator evaluator;
    try {
        static_cast<void>(evaluator.evaluate(identifier));
    } catch (const std::runtime_error& error) {
        return std::string(error.what()).find("Variables are not yet supported") != std::string::npos;
    }

    return fail(test_name, "expected runtime_error");
}

bool throws_for_assignment()
{
    constexpr auto test_name = "assignment expression";
    auto value = std::make_unique<IdentifierExpression>(Token(TokenType::Identifier, "y", 1, 5));
    const auto assignment = AssignmentExpression(Token(TokenType::Identifier, "x", 1, 1), std::move(value));

    Evaluator evaluator;
    try {
        static_cast<void>(evaluator.evaluate(assignment));
    } catch (const std::runtime_error& error) {
        return std::string(error.what()).find("Variables are not yet supported") != std::string::npos;
    }

    return fail(test_name, "expected runtime_error");
}

} // namespace

int main()
{
    bool passed = true;

    passed = expects_value("2+3", 5.0) && passed;
    passed = expects_value("10-4", 6.0) && passed;
    passed = expects_value("5*8", 40.0) && passed;
    passed = expects_value("12/3", 4.0) && passed;
    passed = expects_value("2+3*4", 14.0) && passed;
    passed = expects_value("(2+3)*4", 20.0) && passed;
    passed = expects_value("2^3", 8.0) && passed;
    passed = throws_for_identifier() && passed;
    passed = throws_for_assignment() && passed;

    return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}

