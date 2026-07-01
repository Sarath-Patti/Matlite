#pragma once

#include "ast/Expression.h"
#include "lexer/Token.h"

#include <cstddef>
#include <memory>
#include <vector>

namespace matlite::parser {

class Parser {
public:
    explicit Parser(std::vector<lexer::Token> tokens);

    [[nodiscard]] std::unique_ptr<ast::Expression> parse();

private:
    [[nodiscard]] std::unique_ptr<ast::Expression> parse_assignment();
    [[nodiscard]] std::unique_ptr<ast::Expression> parse_addition();
    [[nodiscard]] std::unique_ptr<ast::Expression> parse_multiplication();
    [[nodiscard]] std::unique_ptr<ast::Expression> parse_power();
    [[nodiscard]] std::unique_ptr<ast::Expression> parse_primary();

    [[nodiscard]] bool is_at_end() const noexcept;
    [[nodiscard]] bool check(lexer::TokenType type) const noexcept;
    [[nodiscard]] bool check_next(lexer::TokenType type) const noexcept;
    [[nodiscard]] const lexer::Token& current() const noexcept;
    [[nodiscard]] const lexer::Token& previous() const noexcept;

    bool match(lexer::TokenType type) noexcept;
    const lexer::Token& advance() noexcept;

    std::vector<lexer::Token> tokens_;
    std::size_t current_ {0};
};

} // namespace matlite::parser
