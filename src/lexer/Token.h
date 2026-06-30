#pragma once

#include <cstddef>
#include <string>

namespace matlite::lexer {

enum class TokenType
{
    // Literals
    Identifier,
    Integer,
    Float,

    // Operators
    Plus,
    Minus,
    Multiply,
    Divide,
    Power,
    Assign,

    // Delimiters
    LeftParen,
    RightParen,
    LeftBracket,
    RightBracket,
    Comma,
    Semicolon,

    // Special
    EndOfFile,
    Invalid
};

struct Token
{
    TokenType type;
    std::string lexeme;
    std::size_t line;
    std::size_t column;
};

} // namespace matlite::lexer