#pragma once

#include <string>
#include <utility>

namespace matlite::lexer {

enum class TokenType {
    Identifier,
    Integer,
    Float,
    Plus,
    Minus,
    Multiply,
    Divide,
    Power,
    Assign,
    LeftParen,
    RightParen,
    LeftBracket,
    RightBracket,
    Comma,
    Semicolon,
    EndOfFile,
    Invalid
};

class Token {
public:
    Token(TokenType type, std::string lexeme, int line, int column);

    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

} // namespace matlite::lexer
