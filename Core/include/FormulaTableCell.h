#pragma once

#include <Table.h>
#include "TableCell.h"
#include "../src/Token.h"
#include "../src/TableCellPosition.h"

namespace core {

    class FormulaTableCell : public TableCell {
    public:
        explicit FormulaTableCell(
                std::string formula,
                TableCellPosition tablePosition,
                const Table &table);

        std::string getDisplayValue() override;

        std::string getValue() override;

        std::vector<TableCellPosition> getTablePositionDependencies() const;

        CellType getType() const override;

        ~FormulaTableCell() override;

    private:
        TableCellPosition _tableCellPosition;
        const Table &_table;
        std::string _formula;
        std::vector<Token> _tokenizedFormula;
        std::vector<TableCellPosition> _tableCells;
        std::vector<unsigned long> _bracketMatches;

        double _calculate();

        void _tokenizeFormula(std::string formula);

        double _calculate(long startIndex, long endIndex);

        void _matchBrackets();

        void _requireValidFormat(const std::string &formula) const;

        long _findExpressionSplitIndex(long startIndex, long endIndex) const;

        double _evaluateToken(const Token &token);

        void _requireNoTableCellConflicts(const FormulaTableCell &cell);

        void _requireNoTableCellConflicts(const FormulaTableCell &cell, std::vector<std::vector<size_t>> &visitedCells);

        double _getValueFromTable(const std::string &cellIdentifier);
    };
}