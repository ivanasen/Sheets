#include "Table.h"
#include "TableFormulaCalculator.h"
#include <iostream>

namespace SheetsCore {
    std::string Table::getCellValue(unsigned row, unsigned col) const {
        if (row > _tableValues.size() - 1 || col > _tableValues.size() - 1) {
            return "";
        }

        TableCell cell = _tableValues[row][col];

        if (cell.getType() == CellType::FORMULA) {
            return TableFormulaCalculator::calculateFormula(cell.getValue());
        }

        return _tableValues[row][col].getValue();
    }

    Table::Table(unsigned initialHeight, unsigned initialWidth)
            : _tableValues(initialHeight, std::vector<TableCell>(initialWidth)) {
    }

    void Table::setCellValue(unsigned row, unsigned col, const std::string &cellValue) {
        _resizeIfNeeded(row + 1, col + 1);

        TableCell newCell = TableCellParser::parse(cellValue);

        if (newCell.getType() == CellType::FORMULA) {
            //TODO: Evaluate formula
        }

        _tableValues[row][col] = newCell;
    }

    void Table::_resizeIfNeeded(unsigned requiredHeight, unsigned requiredWidth) {
        if (requiredHeight > _tableValues.size()) {
            _tableValues.resize(requiredHeight);
        }

        if ((_tableValues.empty() && requiredWidth > 0) || requiredWidth > _tableValues[0].size()) {
            for (std::vector<TableCell> &row : _tableValues) {
                row.resize(requiredWidth);
            }
        }
    }

    Table::Table() : Table(DEFAULT_INITIAL_HEIGHT, DEFAULT_INITIAL_WIDTH) {
    }

}

