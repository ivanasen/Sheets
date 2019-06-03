#include <utility>
#include <stack>

#include "FormulaTableCell.h"
#include "Strings.h"
#include "ArithmeticFormulasUtils.h"
#include "TokenValues.h"
#include "IntegerTableCell.h"
#include "DecimalTableCell.h"
#include <iostream>

namespace core {

    FormulaTableCell::FormulaTableCell(
            std::string formula,
            TableCellPosition position,
            Table &table)
            : _formula(std::move(formula)),
              _tableCellPosition(position),
              _table(table) {
        _tokenizeFormula(getValue());
        _matchBrackets();
    }

    std::string FormulaTableCell::getDisplayValue() {
        double result = _calculate();
        std::string formattedResult = utils::Strings::formatAsDisplayDecimalValue(result);
        return formattedResult;
    }

    std::string FormulaTableCell::getValue() {
        return _formula;
    }

    CellType FormulaTableCell::getType() const {
        return CellType::FORMULA;
    }

    FormulaTableCell::~FormulaTableCell() = default;

    std::vector<TableCellPosition> FormulaTableCell::getTablePositionDependencies() const {
        return _tableCells;
    }

    double FormulaTableCell::_calculate() {
        _requireNoTableCellConflicts(*this);
        double result = _calculate(0, _tokenizedFormula.size() - 1);
        return result;
    }

    double FormulaTableCell::_calculate(
            long startIndex,
            long endIndex) {

        if (startIndex > endIndex
            || startIndex >= _tokenizedFormula.size()
            || endIndex >= _tokenizedFormula.size()) {
            throw std::invalid_argument("Invalid formula: \"" + getValue() + "\"");
        }

        if (_tokenizedFormula[endIndex] == TOKEN_VALUES[(int) TokenType::CLOSING_PARENTHESIS] &&
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

    void FormulaTableCell::_tokenizeFormula(std::string formula) {
        _requireValidFormat(formula);

        const char decimalSeparator = TOKEN_VALUES[(int) TokenType::DECIMAL_SEPARATOR].value[0];
        const char openingParenthesis = TOKEN_VALUES[(int) TokenType::OPENING_PARENTHESIS].value[0];
        const char closingParenthesis = TOKEN_VALUES[(int) TokenType::CLOSING_PARENTHESIS].value[0];
        const char rowIdentifier = TOKEN_VALUES[(int) TokenType::ROW].value[0];

        for (int i = 1; i < formula.size(); i++) {
            std::string toBeExtractedFrom = formula.substr(i, formula.size() - i);

            if (std::isspace(formula[i])) {
                continue;
            } else if (std::isdigit(formula[i]) || formula[i] == decimalSeparator) {
                Token token = ArithmeticFormulasUtils::extractPotentialNumberToken(toBeExtractedFrom);
                _tokenizedFormula.push_back(token);
                i += token.value.size() - 1;
            } else if (formula[i] == openingParenthesis) {
                _tokenizedFormula.push_back(TOKEN_VALUES[(int) TokenType::OPENING_PARENTHESIS]);
            } else if (formula[i] == closingParenthesis) {
                _tokenizedFormula.push_back(TOKEN_VALUES[(int) TokenType::CLOSING_PARENTHESIS]);
            } else if (toupper(formula[i]) == rowIdentifier) {
                Token token = ArithmeticFormulasUtils::extractPotentialIdentifierToken(toBeExtractedFrom);
                _tokenizedFormula.push_back(token);
                i += token.value.size() - 1;

                if (token.type == TokenType::IDENTIFIER) {
                    TableCellPosition position(token.value);
                    _tableCells.push_back(position);
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

    void FormulaTableCell::_matchBrackets() {
        _bracketMatches.resize(_tokenizedFormula.size());
        std::stack<std::pair<char, unsigned long>> bracketsStack;

        for (unsigned long i = 0; i < _tokenizedFormula.size(); i++) {
            if (_tokenizedFormula[i] == TOKEN_VALUES[(int) TokenType::OPENING_PARENTHESIS]) {
                bracketsStack.emplace('(', i);
            } else if (_tokenizedFormula[i] == TOKEN_VALUES[(int) TokenType::CLOSING_PARENTHESIS]) {
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
        if (!ArithmeticFormulasUtils::isFormula(formula)) {
            throw std::invalid_argument("Invalid formula: \"" + formula + "\"");
        }
    }

    double FormulaTableCell::_evaluateToken(const Token &token) {
        switch (token.type) {
            case TokenType::NUMBER:
                return std::stod(token.value);
            case TokenType::STRING:
                return 0;
            case TokenType::IDENTIFIER:
                return _getValueFromTable(token.value);
            default:
                throw std::invalid_argument("Unsupported token type");
        }
    }

    long FormulaTableCell::_findExpressionSplitIndex(long startIndex, long endIndex) const {
        long splitIndex = 0;
        int minSplitPrecedence = 3;

        for (long i = endIndex; i >= startIndex; i--) {
            if (_tokenizedFormula[i] == TOKEN_VALUES[(int) TokenType::CLOSING_PARENTHESIS]) {
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

    void FormulaTableCell::_requireNoTableCellConflicts(const FormulaTableCell &cell) {
        std::vector<std::vector<size_t>> visitedCells(
                _table.getHeight(),
                std::vector<size_t>(_table.getWidth())
        );
        _requireNoTableCellConflicts(cell, visitedCells);
    }

    void FormulaTableCell::_requireNoTableCellConflicts(
            const FormulaTableCell &cell,
            std::vector<std::vector<size_t>> &visitedCells) {
        std::vector<TableCellPosition> cellPositions = cell.getTablePositionDependencies();

        for (const TableCellPosition &pos : cellPositions) {
            if (_tableCellPosition == pos) {
                throw std::invalid_argument("Formula cell can\'t reference itself");
            }

            if (visitedCells[pos.getRow()][pos.getColumn()]) {
                return;
            }

            visitedCells[pos.getRow()][pos.getColumn()] = true;

            const TableCell *containedCell = _table.getCell(pos);
            if (containedCell != nullptr && containedCell->getType() == CellType::FORMULA) {
                FormulaTableCell formula = *((FormulaTableCell *) containedCell);
                _requireNoTableCellConflicts(formula, visitedCells);
            }
        }
    }

    TableCell *FormulaTableCell::clone() {
        auto *newCell = new FormulaTableCell(_formula, _tableCellPosition, _table);
        return newCell;
    }

    double FormulaTableCell::_getValueFromTable(const std::string &cellIdentifier) {
        const TableCell *cell = _table.getCell(TableCellPosition(cellIdentifier));

        if (cell != nullptr) {
            switch (cell->getType()) {
                case CellType::INTEGER:
                    return ((IntegerTableCell *) cell)->getIntValue();
                case CellType::DECIMAL:
                    return ((DecimalTableCell *) cell)->getDecimalValue();
                default:
                    return 0;
            }
        }

        return 0;
    }

    void FormulaTableCell::setTable(const Table &table) {
        _table = table;
    }
}
