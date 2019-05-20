#include <regex>
#include <string>
#include "Constants.cpp"
#include "TokenValues.h"
#include "ArithmeticFormulasUtils.h"
#include "StringUtils.h"

namespace SheetsCore {
    bool ArithmeticFormulasUtils::isTableCellIdentifier(const std::string &s) {
        return std::regex_match(s, TABLE_CELL_FORMAT);
    }

    bool ArithmeticFormulasUtils::isFormula(const std::string &s) {
        return std::string(1, s[0]) == TOKEN_VALUES[TokenType::EQUAL].value;
    }

    bool ArithmeticFormulasUtils::isOperator(const std::string &s) {
        return s == TOKEN_VALUES[TokenType::PLUS].value ||
               s == TOKEN_VALUES[TokenType::MINUS].value ||
               s == TOKEN_VALUES[TokenType::MULTIPLICATION].value ||
               s == TOKEN_VALUES[TokenType::DIVISION].value;
    }

    bool ArithmeticFormulasUtils::isOperator(char c) {
        return isOperator(std::string(1, c));
    }

    bool ArithmeticFormulasUtils::isOperator(const TokenType &t) {
        return t == TokenType::PLUS ||
               t == TokenType::MINUS ||
               t == TokenType::MULTIPLICATION ||
               t == TokenType::DIVISION;
    }

    Token ArithmeticFormulasUtils::getArithmeticOperatorToken(const std::string &s) {
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

    Token ArithmeticFormulasUtils::getArithmeticOperatorToken(char c) {
        return getArithmeticOperatorToken(std::string(1, c));
    }

    int ArithmeticFormulasUtils::getOperatorPrecedence(TokenType token) {
        if (token == TokenType::PLUS || token == TokenType::MINUS) {
            return 1;
        } else if (token == TokenType::MULTIPLICATION || token == TokenType::DIVISION) {
            return 2;
        } else {
            return -1;
        }
    }

    int ArithmeticFormulasUtils::getOperatorPrecedence(const Token &token) {
        return getOperatorPrecedence(token.type);
    }

    double ArithmeticFormulasUtils::applyOperator(double &leftOperand, double &rightOperand, const Token &op) {
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


    Token ArithmeticFormulasUtils::extractPotentialNumberToken(std::string s) {
        std::string result;
        char decimalSeparator = TOKEN_VALUES[TokenType::DECIMAL_SEPARATOR].value[0];
        char closingParenthesis = TOKEN_VALUES[TokenType::CLOSING_PARENTHESIS].value[0];

        bool foundDecimalSeparator = false;
        bool isNumber = true;

        std::string::iterator it = s.begin();

        while (it < s.end() && !std::isspace(*it) && *it != closingParenthesis) {
            if (*it == decimalSeparator) {
                if (foundDecimalSeparator) {
                    isNumber = false;
                }

                foundDecimalSeparator = true;
            } else if (!std::isdigit(*it)) {
                isNumber = false;
            }

            result += *(it++);
        }

        if (isNumber) {
            return Token(TokenType::NUMBER, result);
        }

        return Token(TokenType::STRING, result);
    }

    Token ArithmeticFormulasUtils::extractPotentialIdentifierToken(const std::string &s) {
        std::string result;

        Token stringToken = extractStringToken(s);

        if (isTableCellIdentifier(stringToken.value)) {
            return Token(TokenType::IDENTIFIER, stringToken.value);
        } else {
            return stringToken;
        }
    }

    Token ArithmeticFormulasUtils::extractStringToken(std::string s) {
        std::string result;
        std::string::iterator it = s.begin();

        while (it < s.end() && !std::isspace(*it)) {
            result += *(it++);
        }

        return Token(TokenType::STRING, result);
    }

}
