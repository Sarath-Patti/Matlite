#include "lexer/Lexer.h"
#include "lexer/Token.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace {

using matlite::lexer::Lexer;
using matlite::lexer::Token;
using matlite::lexer::TokenType;

struct ExpectedToken {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

bool expect_tokens(const std::string& name, const std::string& source, const std::vector<ExpectedToken>& expected)
{
    Lexer lexer(source);
    const auto tokens = lexer.tokenize();

    if (tokens.size() != expected.size()) {
        std::cerr << name << ": expected " << expected.size() << " tokens, got " << tokens.size() << '\n';
        return false;
    }

    for (std::size_t index = 0; index < expected.size(); ++index) {
        const Token& actual = tokens[index];
        const ExpectedToken& wanted = expected[index];

        if (actual.type != wanted.type || actual.lexeme != wanted.lexeme || actual.line != wanted.line
            || actual.column != wanted.column) {
            std::cerr << name << ": token " << index << " mismatch\n";
            std::cerr << "  expected lexeme '" << wanted.lexeme << "' at " << wanted.line << ':' << wanted.column
                      << '\n';
            std::cerr << "  got lexeme '" << actual.lexeme << "' at " << actual.line << ':' << actual.column << '\n';
            return false;
        }
    }

    return true;
}

} // namespace

int main()
{
    bool passed = true;

    passed = expect_tokens(
                 "operators and delimiters",
                 "+ - * / ^ = ( ) [ ] , ;",
                 {
                     {TokenType::Plus, "+", 1, 1},
                     {TokenType::Minus, "-", 1, 3},
                     {TokenType::Multiply, "*", 1, 5},
                     {TokenType::Divide, "/", 1, 7},
                     {TokenType::Power, "^", 1, 9},
                     {TokenType::Assign, "=", 1, 11},
                     {TokenType::LeftParen, "(", 1, 13},
                     {TokenType::RightParen, ")", 1, 15},
                     {TokenType::LeftBracket, "[", 1, 17},
                     {TokenType::RightBracket, "]", 1, 19},
                     {TokenType::Comma, ",", 1, 21},
                     {TokenType::Semicolon, ";", 1, 23},
                     {TokenType::EndOfFile, "", 1, 24},
                 })
        && passed;

    passed = expect_tokens(
                 "identifiers and numbers",
                 "alpha beta_2 42 3.14",
                 {
                     {TokenType::Identifier, "alpha", 1, 1},
                     {TokenType::Identifier, "beta_2", 1, 7},
                     {TokenType::Integer, "42", 1, 14},
                     {TokenType::Float, "3.14", 1, 17},
                     {TokenType::EndOfFile, "", 1, 21},
                 })
        && passed;

    passed = expect_tokens(
                 "line and column tracking",
                 "a = 1\n  b = 2",
                 {
                     {TokenType::Identifier, "a", 1, 1},
                     {TokenType::Assign, "=", 1, 3},
                     {TokenType::Integer, "1", 1, 5},
                     {TokenType::Identifier, "b", 2, 3},
                     {TokenType::Assign, "=", 2, 5},
                     {TokenType::Integer, "2", 2, 7},
                     {TokenType::EndOfFile, "", 2, 8},
                 })
        && passed;

    passed = expect_tokens(
                 "invalid characters",
                 "@ .",
                 {
                     {TokenType::Invalid, "@", 1, 1},
                     {TokenType::Invalid, ".", 1, 3},
                     {TokenType::EndOfFile, "", 1, 4},
                 })
        && passed;

    return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
