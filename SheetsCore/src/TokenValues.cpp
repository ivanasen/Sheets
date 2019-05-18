#include <unordered_map>
#include "TokenType.h"

static std::unordered_map<TokenType, std::string> TOKEN_VALUES{
        {TokenType::COMMA,                ","},
        {TokenType::OPENING_PARENTHESIS, "("},
        {TokenType::CLOSING_PARENTHESIS,  ")"},
        {TokenType::PLUS,                 "+"},
        {TokenType::MINUS,                "-"},
        {TokenType::MULTIPLICATION,       "*"},
        {TokenType::DIVISION,             "/"},
        {TokenType::EQUAL,                "="},
        {TokenType::DECIMAL_SEPARATOR,    "."}
};