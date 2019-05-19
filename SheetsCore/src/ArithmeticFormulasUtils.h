#pragma once

#include "TokenType.h"
#include "Token.h"

namespace SheetsCore {
    class ArithmeticFormulasUtils {
    public:
        static bool isTableCellIdentifier(const std::string &s);

        static bool isFormula(const std::string &s);

        static bool isOperator(const std::string &s);

        static bool isOperator(const TokenType &t);

        static Token getArithmeticOperatorToken(const std::string &s);

        static int getOperatorPrecedence(TokenType token);

        static int getOperatorPrecedence(const Token &token);

        static double applyOperator(double &leftOperand, double &rightOperand, const Token &op);

        static std::pair<unsigned long, unsigned long> convertFromIdentifierToRowAndCol(std::string identifier);
    };
}