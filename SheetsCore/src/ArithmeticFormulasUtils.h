#pragma once

#include "TokenType.h"
#include "Token.h"
#include "TableCellPosition.h"

namespace SheetsCore {
    class ArithmeticFormulasUtils {
    public:
        static bool isTableCellIdentifier(const std::string &s);

        static bool isFormula(const std::string &s);

        static bool isOperator(const std::string &s);

        static bool isOperator(const TokenType &t);

        static Token getArithmeticOperatorToken(const std::string &s);

        static Token getArithmeticOperatorToken(char c);

        static int getOperatorPrecedence(TokenType token);

        static int getOperatorPrecedence(const Token &token);

        static double applyOperator(double &leftOperand, double &rightOperand, const Token &op);

        static TableCellPosition convertFromIdentifierToTablePosition(std::string identifier);

        static bool isOperator(char c);

        static Token extractPotentialNumberToken(std::string s);

        static Token extractStringToken(std::string s);

        static Token extractPotentialIdentifierToken(std::string s);
    };
}