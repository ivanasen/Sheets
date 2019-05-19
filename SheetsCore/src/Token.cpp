#include "Token.h"

namespace SheetsCore {


    Token::Token(TokenType type, std::string value)
            : type(type), value(std::move(value)) {
    }

    Token::Token() : value(""), type(TokenType::IDENTIFIER) {
    }

    bool Token::operator==(const Token &other) const {
        return other.type == type && other.value == value;
    }
}