#include "lexer/Token.h"

namespace matlite::lexer {

Token::Token(TokenType type, std::string lexeme, int line, int column)
    : type(type)
    , lexeme(std::move(lexeme))
    , line(line)
    , column(column)
{
}

} // namespace matlite::lexer
