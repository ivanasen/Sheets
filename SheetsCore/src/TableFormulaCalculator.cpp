#include "TableFormulaCalculator.h"
#include "TokenValues.h"
#include "StringUtils.cpp"

std::string TableFormulaCalculator::calculateFormula(const std::string &formula) {
    std::vector<std::string> separated = splitBySpaces(formula);
    _requireValidFormat(separated);

    //Split Formula...

    std::vector<Token> tokens = _tokenizeFormula(separated);

    //Make sure formula is correct

    //Make sure there are no recursive calls

    //Calculate...
    double result = _evaluateFormula(tokens);

    return std::to_string(result);
}

std::vector<Token> TableFormulaCalculator::_tokenizeFormula(std::vector<std::string> formula) {
    //Remove equals sign
    formula.erase(formula.begin());

    std::vector<Token> tokens;

    for (const std::string &s : formula) {
        if (isInteger(s) || isDecimal(s)) {
            tokens.emplace_back(TokenType::NUMBER, s);
        } else if (isTableCellIdentifier(s)) {
            tokens.emplace_back(TokenType::IDENTIFIER, s);
        } else if (isOperator(s)) {
            tokens.emplace_back(getArithmeticOperatorToken(s));
        } else {
            tokens.emplace_back(TokenType::STRING, s);
        }
    }

    return tokens;
}

void TableFormulaCalculator::_requireValidFormat(std::vector<std::string> formula) {
    std::string equalsSign = TOKEN_VALUES[TokenType::EQUAL].value;
    if (formula[0] != equalsSign) {
        throw std::invalid_argument("Invalid formula: \"" + formula[0] + "\"");
    }
}

std::vector<unsigned long> TableFormulaCalculator::_matchBrackets(const std::vector<Token> &formula) {
    std::vector<unsigned long> matches;
    std::stack<std::pair<char, unsigned long>> bracketsStack;

    for (unsigned long i = 0; i < formula.size(); i++) {
        if (formula[i] == TOKEN_VALUES[TokenType::OPENING_PARENTHESIS]) {
            bracketsStack.emplace('(', i);
        } else if (formula[i] == TOKEN_VALUES[TokenType::CLOSING_PARENTHESIS]) {
            std::pair<char, unsigned long> top = bracketsStack.top();

            if (top.first == '(') {
                matches[i] = top.second;
            } else {
                std::string exception = "Missing opening bracket for position " + std::to_string(i);
                throw std::invalid_argument(exception);
            }
            bracketsStack.pop();
        }
    }

    if (!bracketsStack.empty()) {
        std::pair<char, int> top = bracketsStack.top();
        std::string exception = "Missing closing bracket for position " + std::to_string(top.second);
        throw std::invalid_argument(exception);
    }

    return matches;
}

double TableFormulaCalculator::_evaluateFormula(const std::vector<Token> &tokens) {
    std::vector<unsigned long> bracketMatches = _matchBrackets(tokens);
    return _evaluateFormula(tokens, bracketMatches, 0, tokens.size() - 1);
}

double TableFormulaCalculator::_evaluateFormula(
        const std::vector<Token> &formula,
        std::vector<unsigned long> &bracketMatches,
        unsigned long startIndex,
        unsigned long endIndex) {
    if (formula[endIndex] == TOKEN_VALUES[TokenType::CLOSING_PARENTHESIS] && bracketMatches[endIndex] == startIndex) {
        return _evaluateFormula(formula, bracketMatches, startIndex + 1, endIndex - 1);
    }

    if (startIndex == endIndex) {
        return _evaluateToken(formula[startIndex]);
    }

    long splitIndex = _findExpressionSplitIndex(formula, bracketMatches, startIndex, endIndex);

    double leftResult = _evaluateFormula(formula, bracketMatches, startIndex, splitIndex - 1);
    double rightResult = _evaluateFormula(formula, bracketMatches, splitIndex + 1, endIndex);

    double result = applyOperator(leftResult, rightResult, formula[splitIndex]);

    return result;
}

double TableFormulaCalculator::_evaluateToken(const Token &token) {
    if (token.type == TokenType::NUMBER) {
        return std::stod(token.value);
    } else if (token.type == TokenType::STRING) {
        return 0;
    } else if (token.type == TokenType::IDENTIFIER) {
        //Get identifier value
        return 0;
    }
    return 0;
}

long TableFormulaCalculator::_findExpressionSplitIndex(
        const std::vector<Token> &formula,
        std::vector<unsigned long> &bracketMatches,
        unsigned long startIndex,
        unsigned long endIndex) {
    long splitIndex = 0;
    int minSplitPrecedence = 3;

    for (long i = endIndex; i >= startIndex; i--) {
        if (formula[i] == TOKEN_VALUES[TokenType::CLOSING_PARENTHESIS]) {
            i = bracketMatches[i];
        }

        if (isOperator(formula[i].type) &&
            (splitIndex == 0 || getOperatorPrecedence(formula[i]) < minSplitPrecedence)) {
            splitIndex = i;
            minSplitPrecedence = getOperatorPrecedence(formula[i]);
        }
    }

    return splitIndex;
}

//double evaluateValue(const std::string &value, const Table &table) {
//    //If value is a literal return
//
//    //if value is number or string from table return value
//
//    //if value is a formula check for dependencies in table:
//        //1. Get all variables from formula
//        //2. Check if current variable persists in that formula
//        //  2.1. If yes then throw exception
//        //  2.2. If no then traverse by dfs all other potential formulas
//        //  2.3. If current formula is not present in all other dependant formulas then OK, else throw
//        //3. Return value
//
//}
