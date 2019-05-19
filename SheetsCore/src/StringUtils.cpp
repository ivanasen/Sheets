#include <string>
#include <vector>
#include "TokenType.h"
#include "Token.h"
#include "TokenValues.h"
#include "Constants.cpp"

static void ltrim(std::string &string) {
    std::string::iterator endTrimPosition = string.begin();

    while (std::isspace(*endTrimPosition)) {
        endTrimPosition++;
    }

    string.erase(string.begin(), endTrimPosition);
}

static void rtrim(std::string &string) {
    std::string::iterator endTrimPosition = string.end() - 1;
    while (std::isspace(*endTrimPosition)) {
        endTrimPosition--;
    }
    if (endTrimPosition < string.end()) {
        string.erase(endTrimPosition + 1, string.end());
    }
}

static void trim(std::string &string) {
    ltrim(string);
    rtrim(string);
}


static std::vector<std::string> splitBySpaces(const std::string &string) {
    std::vector<std::string> separated;
    auto iterator = string.begin();

    while (iterator != string.end()) {
        if (std::isspace(*iterator)) {
            iterator++;
        } else {
            std::string newElement;
            while (iterator != string.end() && !std::isspace(*iterator)) {
                newElement.push_back(*iterator);
            }
            separated.push_back(newElement);
        }
    }

    return separated;
}

static std::vector<std::string> split(const std::string &string, char separator) {
    std::vector<std::string> separated;
    auto iterator = string.begin();

    while (iterator != string.end()) {
        if (*iterator == separator) {
            iterator++;
        } else {
            std::string newElement;
            while (iterator != string.end() && *iterator != separator) {
                newElement.push_back(*iterator++);
            }
            separated.push_back(newElement);
        }
    }

    return separated;
}

static bool isTableCellIdentifier(const std::string &s) {
    return std::regex_match(s, TABLE_CELL_FORMAT);
}

static bool isFormula(const std::string &s) {
    return std::string(1, s[0]) == TOKEN_VALUES[TokenType::EQUAL].value;
}

static bool isOperator(const std::string &s) {
    return s == TOKEN_VALUES[TokenType::PLUS].value ||
           s == TOKEN_VALUES[TokenType::MINUS].value ||
           s == TOKEN_VALUES[TokenType::MULTIPLICATION].value ||
           s == TOKEN_VALUES[TokenType::DIVISION].value;
}

static bool isOperator(const TokenType &t) {
    return t == TokenType::PLUS ||
           t == TokenType::MINUS ||
           t == TokenType::MULTIPLICATION ||
           t == TokenType::DIVISION;
}

static Token getArithmeticOperatorToken(const std::string &s) {
    if (s == TOKEN_VALUES[TokenType::PLUS].value) {
        return TOKEN_VALUES[TokenType::PLUS];
    } else if (s == TOKEN_VALUES[TokenType::MINUS].value) {
        return TOKEN_VALUES[TokenType::MINUS];
    } else if (s == TOKEN_VALUES[TokenType::MULTIPLICATION].value) {
        return TOKEN_VALUES[TokenType::MULTIPLICATION];
    } else if (s == TOKEN_VALUES[TokenType::DIVISION].value) {
        return TOKEN_VALUES[TokenType::DIVISION];
    } else {
        throw std::invalid_argument("\"s\" is not an arithmetic operator");
    }
}

static bool isInteger(const std::string &s) {
    std::string trimmed = s;
    trim(trimmed);

    for (char c : trimmed) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

static bool isDecimal(const std::string &s) {
    std::string trimmed = s;
    trim(trimmed);

    Token decimalSeparator = TOKEN_VALUES[TokenType::DECIMAL_SEPARATOR];
    bool foundDecimalSeparator = false;
    for (char c : trimmed) {
        if (std::isdigit(c)) {
            continue;
        } else if (std::string(1, c) == decimalSeparator.value) {
            if (foundDecimalSeparator) {
                return false;
            }
            foundDecimalSeparator = true;
        } else {
            return false;
        }
    }
    return !s.empty();
}

static int getOperatorPrecedence(TokenType token) {
    if (token == TokenType::PLUS || token == TokenType::MINUS) {
        return 1;
    } else if (token == TokenType::MULTIPLICATION || token == TokenType::DIVISION) {
        return 2;
    } else {
        return -1;
    }
}

static int getOperatorPrecedence(const Token &token) {
    return getOperatorPrecedence(token.type);
}

static double applyOperator(double &leftOperand, double &rightOperand, const Token &op) {
    TokenType operatorType = op.type;
    if (operatorType == TokenType::PLUS) {
        return leftOperand + rightOperand;
    } else if (operatorType == TokenType::MINUS) {
        return leftOperand - rightOperand;
    } else if (operatorType == TokenType::MULTIPLICATION) {
        return leftOperand * rightOperand;
    } else if (operatorType == TokenType::DIVISION) {
        return leftOperand / rightOperand;
    } else {
        throw std::invalid_argument("Invalid operator: \"" + op.value + "\"");
    }
}