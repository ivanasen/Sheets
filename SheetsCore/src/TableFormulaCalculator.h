#pragma once

#include <string>
#include <Table.h>
#include "Token.h"

namespace SheetsCore {

    class TableFormulaCalculator {
    public:
        static std::string calculateFormula(const std::string &formula);

        static std::vector<Token> tokenizeFormula(const std::string &formula);

        static std::vector<unsigned long> matchBrackets(const std::vector<Token> &formula);

        static double evaluateFormula(const std::vector<Token> &tokens);

        static double
        evaluateFormula(
                const std::vector<Token> &formula,
                std::vector<unsigned long> &bracketMatches,
                unsigned long startIndex,
                unsigned long endIndex);

        static double evaluateToken(const Token &token);

        static long
        findExpressionSplitIndex(
                const std::vector<Token> &formula,
                std::vector<unsigned long> &bracketMatches,
                long startIndex,
                long endIndex);

    private:
        Table table;

        static void _requireValidFormat(std::vector<std::string> formula);
    };

}