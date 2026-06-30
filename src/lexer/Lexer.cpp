#include "lexer/Lexer.h"

#include <cctype>
#include <string>
#include <utility>

namespace matlite::lexer {

namespace {

bool is_identifier_start(char value)
{
    const auto character = static_cast<unsigned char>(value);
    return std::isalpha(character) != 0 || value == '_';
}

bool is_identifier_part(char value)
{
    const auto character = static_cast<unsigned char>(value);
    return std::isalnum(character) != 0 || value == '_';
}

bool is_digit(char value)
{
    const auto character = static_cast<unsigned char>(value);
    return std::isdigit(character) != 0;
}

} // namespace

Lexer::Lexer(std::string source)
    : source_(std::move(source))
{
}

std::vector<Token> Lexer::tokenize()
{
    tokens_.clear();
    position_ = 0;
    line_ = 1;
    column_ = 1;

    while (!is_at_end()) {
        const auto token_line = line_;
        const auto token_column = column_;
        const auto value = current();

        if (value == ' ' || value == '\t' || value == '\r') {
            advance();
            continue;
        }

        if (value == '\n') {
            advance();
            continue;
        }

        if (is_identifier_start(value)) {
            scan_identifier();
            continue;
        }

        if (is_digit(value)) {
            scan_number();
            continue;
        }

        switch (value) {
        case '+':
            advance();
            add_token(TokenType::Plus, "+", token_line, token_column);
            break;
        case '-':
            advance();
            add_token(TokenType::Minus, "-", token_line, token_column);
            break;
        case '*':
            advance();
            add_token(TokenType::Multiply, "*", token_line, token_column);
            break;
        case '/':
            advance();
            add_token(TokenType::Divide, "/", token_line, token_column);
            break;
        case '^':
            advance();
            add_token(TokenType::Power, "^", token_line, token_column);
            break;
        case '=':
            advance();
            add_token(TokenType::Assign, "=", token_line, token_column);
            break;
        case '(':
            advance();
            add_token(TokenType::LeftParen, "(", token_line, token_column);
            break;
        case ')':
            advance();
            add_token(TokenType::RightParen, ")", token_line, token_column);
            break;
        case '[':
            advance();
            add_token(TokenType::LeftBracket, "[", token_line, token_column);
            break;
        case ']':
            advance();
            add_token(TokenType::RightBracket, "]", token_line, token_column);
            break;
        case ',':
            advance();
            add_token(TokenType::Comma, ",", token_line, token_column);
            break;
        case ';':
            advance();
            add_token(TokenType::Semicolon, ";", token_line, token_column);
            break;
        default:
            advance();
            add_token(TokenType::Invalid, std::string(1, value), token_line, token_column);
            break;
        }
    }

    add_token(TokenType::EndOfFile, "", line_, column_);
    return tokens_;
}

bool Lexer::is_at_end() const noexcept
{
    return position_ >= source_.size();
}

char Lexer::current() const noexcept
{
    return is_at_end() ? '\0' : source_[position_];
}

char Lexer::peek() const noexcept
{
    const auto next = position_ + 1;
    return next >= source_.size() ? '\0' : source_[next];
}

char Lexer::advance() noexcept
{
    const auto value = source_[position_++];

    if (value == '\n') {
        ++line_;
        column_ = 1;
    } else {
        ++column_;
    }

    return value;
}

void Lexer::add_token(TokenType type, std::string lexeme, int line, int column)
{
    tokens_.emplace_back(type, std::move(lexeme), line, column);
}

void Lexer::scan_identifier()
{
    const auto start = position_;
    const auto token_line = line_;
    const auto token_column = column_;

    while (!is_at_end() && is_identifier_part(current())) {
        advance();
    }

    add_token(
        TokenType::Identifier,
        source_.substr(start, position_ - start),
        token_line,
        token_column
    );
}

void Lexer::scan_number()
{
    const auto start = position_;
    const auto token_line = line_;
    const auto token_column = column_;

    while (!is_at_end() && is_digit(current())) {
        advance();
    }

    auto type = TokenType::Integer;

    if (!is_at_end() && current() == '.' && is_digit(peek())) {
        type = TokenType::Float;
        advance();

        while (!is_at_end() && is_digit(current())) {
            advance();
        }
    }

    add_token(type, source_.substr(start, position_ - start), token_line, token_column);
}

} // namespace matlite::lexer

