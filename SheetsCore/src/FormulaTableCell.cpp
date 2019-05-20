#include <utility>
#include <stack>

#include "FormulaTableCell.h"
#include "StringUtils.h"
#include "ArithmeticFormulasUtils.h"
#include "TokenValues.h"

namespace SheetsCore {

    FormulaTableCell::FormulaTableCell(
            size_t tableRow,
            size_t tableColumn,
            std::string formula,
            const Table &table)
            : TableCell(CellType::FORMULA, std::move(formula)),
              _tableCellPosition(tableRow, tableColumn),
              _table(table) {
        _tokenizeFormula(getFormulaValue());
        _matchBrackets();
    }

    std::string FormulaTableCell::getValue() {
        double result = _calculate();
        return std::to_string(result);
    }

    std::string FormulaTableCell::getFormulaValue() {
        return TableCell::getValue();
    }

    double FormulaTableCell::_calculate() {
        _requireNoTableCellConflicts(*this);
        double result = _calculate(0, _tokenizedFormula.size() - 1);
        return result;
    }

    void FormulaTableCell::_tokenizeFormula(std::string formula) {
        _requireValidFormat(formula);

        const char decimalSeparator = TOKEN_VALUES[TokenType::DECIMAL_SEPARATOR].value[0];
        const char openingParenthesis = TOKEN_VALUES[TokenType::OPENING_PARENTHESIS].value[0];
        const char closingParenthesis = TOKEN_VALUES[TokenType::CLOSING_PARENTHESIS].value[0];
        const char rowIdentifier = TOKEN_VALUES[TokenType::ROW].value[0];

        for (int i = 1; i < formula.size(); i++) {
            std::string toBeExtractedFrom = formula.substr(i, formula.size() - i);

            if (std::isspace(formula[i])) {
                continue;
            } else if (std::isdigit(formula[i]) || formula[i] == decimalSeparator) {
                Token token = ArithmeticFormulasUtils::extractPotentialNumberToken(toBeExtractedFrom);
                _tokenizedFormula.push_back(token);
                i += token.value.size() - 1;
            } else if (formula[i] == openingParenthesis) {
                _tokenizedFormula.push_back(TOKEN_VALUES[TokenType::OPENING_PARENTHESIS]);
            } else if (formula[i] == closingParenthesis) {
                _tokenizedFormula.push_back(TOKEN_VALUES[TokenType::CLOSING_PARENTHESIS]);
            } else if (formula[i] == rowIdentifier) {
                Token token = ArithmeticFormulasUtils::extractPotentialIdentifierToken(toBeExtractedFrom);
                _tokenizedFormula.push_back(token);
                i += token.value.size() - 1;

                if (token.type == TokenType::IDENTIFIER) {
                    TableCellPosition position =
                            ArithmeticFormulasUtils::convertFromIdentifierToTablePosition(token.value);
                    _tabeCells.push_back(position);
                }

            } else if (ArithmeticFormulasUtils::isOperator(formula[i])) {
                Token operatorToken = ArithmeticFormulasUtils::getArithmeticOperatorToken(formula[i]);
                _tokenizedFormula.push_back(operatorToken);
            } else {
                Token stringToken = ArithmeticFormulasUtils::extractStringToken(toBeExtractedFrom);
                _tokenizedFormula.push_back(stringToken);
                i += stringToken.value.size() - 1;
            }
        }
    }

    double FormulaTableCell::_calculate(
            unsigned long startIndex,
            unsigned long endIndex) {
        if (_tokenizedFormula[endIndex] == TOKEN_VALUES[TokenType::CLOSING_PARENTHESIS] &&
            _bracketMatches[endIndex] == startIndex) {
            return _calculate(startIndex + 1, endIndex - 1);
        }

        if (startIndex == endIndex) {
            return _evaluateToken(_tokenizedFormula[startIndex]);
        }

        long splitIndex = _findExpressionSplitIndex(startIndex, endIndex);

        double leftResult = _calculate(startIndex, splitIndex - 1);
        double rightResult = _calculate(splitIndex + 1, endIndex);

        double result = ArithmeticFormulasUtils::applyOperator(leftResult, rightResult, _tokenizedFormula[splitIndex]);

        return result;
    }

    void FormulaTableCell::_matchBrackets() {
        _bracketMatches.resize(_tokenizedFormula.size());
        std::stack<std::pair<char, unsigned long>> bracketsStack;

        for (unsigned long i = 0; i < _tokenizedFormula.size(); i++) {
            if (_tokenizedFormula[i] == TOKEN_VALUES[TokenType::OPENING_PARENTHESIS]) {
                bracketsStack.emplace('(', i);
            } else if (_tokenizedFormula[i] == TOKEN_VALUES[TokenType::CLOSING_PARENTHESIS]) {
                std::pair<char, unsigned long> top = bracketsStack.top();

                if (top.first == '(') {
                    _bracketMatches[i] = top.second;
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
    }

    void FormulaTableCell::_requireValidFormat(const std::string &formula) const {
        char equalsSign = TOKEN_VALUES[TokenType::EQUAL].value[0];
        if (formula[0] != equalsSign) {
            throw std::invalid_argument("Invalid formula: \"" + formula + "\"");
        }
    }


    double FormulaTableCell::_evaluateToken(const Token &token) {
        if (token.type == TokenType::NUMBER) {
            return std::stod(token.value);
        } else if (token.type == TokenType::STRING) {
            return 0;
        } else if (token.type == TokenType::IDENTIFIER) {
            std::string cellValue = _table.getCellValue(token.value);
            if (StringUtils::isDecimal(cellValue)) {
                return std::stod(cellValue);
            }
            return 0;
        }
        return 0;
    }

    long FormulaTableCell::_findExpressionSplitIndex(long startIndex, long endIndex) const {
        long splitIndex = 0;
        int minSplitPrecedence = 3;

        for (long i = endIndex; i >= startIndex; i--) {
            if (_tokenizedFormula[i] == TOKEN_VALUES[TokenType::CLOSING_PARENTHESIS]) {
                i = _bracketMatches[i];
            }

            if (ArithmeticFormulasUtils::isOperator(_tokenizedFormula[i].type) &&
                (splitIndex == 0 ||
                 ArithmeticFormulasUtils::getOperatorPrecedence(_tokenizedFormula[i]) < minSplitPrecedence)) {
                splitIndex = i;
                minSplitPrecedence = ArithmeticFormulasUtils::getOperatorPrecedence(_tokenizedFormula[i]);
            }
        }

        return splitIndex;
    }

    std::vector<TableCellPosition> FormulaTableCell::getContainedTableCellPositions() const {
        return _tabeCells;
    }

    void FormulaTableCell::_requireNoTableCellConflicts(const FormulaTableCell &cell) {
        std::vector<TableCellPosition> cellPositions = cell.getContainedTableCellPositions();

        for (const TableCellPosition &pos : cellPositions) {
            if (_tableCellPosition == pos) {
                throw std::invalid_argument("Formula cell can\'t reference itself");
            }

            std::shared_ptr<TableCell> containedCell = _table.getCell(pos.row, pos.column);
            if (containedCell != nullptr && containedCell->getType() == CellType::FORMULA) {
                FormulaTableCell formula = *std::dynamic_pointer_cast<FormulaTableCell>(containedCell);
                _requireNoTableCellConflicts(formula);
            }
        }
    }
}
