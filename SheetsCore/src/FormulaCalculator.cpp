#include "FormulaCalculator.h"

std::string FormulaCalculator::calculateFormula(const std::string &formula, const Table &table) {
    //Split Formula...

    //Match brackets...

    //Calculate...

    return "";
}

double evaluateValue(const std::string &value, const Table &table) {
    //If value is a literal return

    //if value is number or string from table return value

    //if value is a formula check for dependencies in table:
        //1. Get all variables from formula
        //2. Check if current variable persists in that formula
        //  2.1. If yes then throw exception
        //  2.2. If no then traverse by dfs all other potential formulas
        //  2.3. If current formula is not present in all other dependant formulas then OK, else throw
        //3. Return value

}

//std::vector<std::string> splitExpression(const std::string &expression) {
//    std::vector<std::string> splitExpression;
//
//    for (unsigned i = 0; i < expression.length(); i++) {
//        char currentChar = expression[i];
//
//        if (isOperator(currentChar) || isBracket(currentChar)) {
//            splitExpression.emplace_back(std::string(1, currentChar));
//        } else if (isdigit(currentChar)) {
//            std::string number = extractNumber(expression.substr(i));
//            i += number.length() - 1;
//            splitExpression.push_back(number);
//        } else if (isalpha(currentChar)) {
//            std::string name = extractName(expression.substr(i));
//            i += name.length() - 1;
//            splitExpression.push_back(name);
//        } else if (isWhiteSpace(currentChar)) {
//            continue;
//        } else {
//            throw std::invalid_argument("Invalid expression.");
//        }
//    }
//
//    return splitExpression;
//}
