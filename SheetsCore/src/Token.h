#pragma once

#include <string>
#include "TokenType.h"

struct Token {
    Token();

    Token(TokenType type, std::string value);

    TokenType type;
    std::string value;

    bool operator ==(const Token &other) const;
};