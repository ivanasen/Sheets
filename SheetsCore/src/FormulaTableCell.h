#pragma once

#include <Table.h>
#include "TableCell.h"
#include "Token.h"
#include "TableCellPosition.h"

namespace SheetsCore {

    class FormulaTableCell : public TableCell {
    public:
        explicit FormulaTableCell(size_t tableRow, size_t tableColumn, std::string formula, const Table &table);

        std::string getValue() override;

        std::string getFormulaValue();

        std::vector<TableCellPosition> getContainedTableCellPositions() const;

    private:
        TableCellPosition _tableCellPosition;
        const Table &_table;
        std::vector<Token> _tokenizedFormula;
        std::vector<TableCellPosition> _tabeCells;
        std::vector<unsigned long> _bracketMatches;

        double _calculate();

        void _tokenizeFormula(std::string formula);

        double _calculate(unsigned long startIndex, unsigned long endIndex);

        void _matchBrackets();

        void _requireValidFormat(const std::string &formula) const;

        long _findExpressionSplitIndex(long startIndex, long endIndex) const;

        double _evaluateToken(const Token &token);

        void _requireNoTableCellConflicts(const FormulaTableCell &cell);
    };
}