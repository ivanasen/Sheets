#pragma once

#include <string>
#include <Table.h>
#include "Token.h"

class TableFormulaCalculator {
public:
    static std::string calculateFormula(const std::string &formula);

private:
    Table table;

    static std::vector<Token> _tokenizeFormula(std::vector<std::string> formula);

    static void _requireValidFormat(std::vector<std::string> basicString);

    static std::vector<unsigned long> _matchBrackets(const std::vector<Token> &vector);

    static double _evaluateFormula(const std::vector<Token> &tokens);

    static double
    _evaluateFormula(
            const std::vector<Token> &formula,
            std::vector<unsigned long> &bracketMatches,
            unsigned long startIndex,
            unsigned long endIndex);

    static double _evaluateToken(const Token &token);

    static long
    _findExpressionSplitIndex(const std::vector<Token> &formula, std::vector<unsigned long> &bracketMatches, unsigned long startIndex,
                              unsigned long endIndex);
};