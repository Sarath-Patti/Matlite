#pragma once

#include "lexer/Token.h"

#include <string>
#include <vector>

namespace matlite::lexer {

class Lexer {
public:
    explicit Lexer(std::string source);

    [[nodiscard]] std::vector<Token> tokenize();

private:
    [[nodiscard]] bool is_at_end() const noexcept;
    [[nodiscard]] char current() const noexcept;
    [[nodiscard]] char peek() const noexcept;

    char advance() noexcept;
    void add_token(TokenType type, std::string lexeme, int line, int column);
    void scan_identifier();
    void scan_number();

    std::string source_;
    std::size_t position_ {0};
    int line_ {1};
    int column_ {1};
    std::vector<Token> tokens_;
};

} // namespace matlite::lexer

