#pragma once

#include "Table.h"
#include "TableCell.h"
#include "Token.h"
#include "../src/TableCellPosition.h"

namespace core {

    class FormulaTableCell : public TableCell {
    public:
        explicit FormulaTableCell(
                std::string formula,
                TableCellPosition tablePosition,
                Table &table);

        std::string getDisplayValue() override;

        std::string getValue() override;

        std::vector<TableCellPosition> getTablePositionDependencies() const;

        CellType getType() const override;

        TableCell *clone() override;

        void setTable(const Table &table);

        ~FormulaTableCell() override;

    private:
        TableCellPosition _tableCellPosition;
        Table &_table;
        std::string _formula;
        std::vector<Token> _tokenizedFormula;
        std::vector<TableCellPosition> _tableCells;
        std::vector<unsigned long> _bracketMatches;

        double calculate();

        void tokenizeFormula(std::string formula);

        double calculate(long startIndex, long endIndex);

        void matchBrackets();

        void requireValidFormat(const std::string &formula) const;

        long findExpressionSplitIndex(long startIndex, long endIndex) const;

        double evaluateToken(const Token &token);

        void requireNoTableCellConflicts(const FormulaTableCell &cell);

        void requireNoTableCellConflicts(const FormulaTableCell &cell, std::vector<std::vector<size_t>> &visitedCells);

        double getValueFromTable(const std::string &cellIdentifier);
    };
}