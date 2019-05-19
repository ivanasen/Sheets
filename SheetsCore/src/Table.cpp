#include "Table.h"
#include "TableFormulaCalculator.h"
#include "StringUtils.h"
#include "ArithmeticFormulasUtils.h"
#include "TokenValues.h"
#include <iostream>

namespace SheetsCore {
    const int Table::DEFAULT_INITIAL_HEIGHT = 10;
    const int Table::DEFAULT_INITIAL_WIDTH = 10;

    std::string Table::getCellValue(unsigned row, unsigned col) const {
        if (row > _cells.size() - 1 || (!_cells.empty() && col > _cells[0].size() - 1)) {
            return "";
        }

        TableCell cell = _cells[row][col];

        if (cell.getType() == CellType::FORMULA) {
            return TableFormulaCalculator::calculateFormula(cell.getValue());
        }

        return _cells[row][col].getValue();
    }

    Table::Table(unsigned initialHeight, unsigned initialWidth)
            : _cells(initialHeight, std::vector<TableCell>(initialWidth)) {
    }

    void Table::setCellValue(unsigned row, unsigned col, const std::string &cellValue) {
        _resizeIfNeeded(row + 1, col + 1);

        TableCell newCell = TableCellParser::parse(cellValue);

        if (newCell.getType() == CellType::FORMULA) {
            //TODO: Evaluate formula
        }

        _cells[row][col] = newCell;
    }

    void Table::_resizeIfNeeded(unsigned requiredHeight, unsigned requiredWidth) {
        if (requiredHeight > _cells.size()) {
            _cells.resize(requiredHeight);
        }

        if ((_cells.empty() && requiredWidth > 0) || requiredWidth > _cells[0].size()) {
            for (std::vector<TableCell> &row : _cells) {
                row.resize(requiredWidth);
            }
        }
    }

    Table::Table() : Table(DEFAULT_INITIAL_HEIGHT, DEFAULT_INITIAL_WIDTH) {
    }

    std::vector<std::vector<std::string>> Table::getAllCellValues() const {
        std::vector<std::vector<std::string>> result(
                _cells.size(),
                std::vector<std::string>(_cells[0].size()));

        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[0].size(); j++) {
                result[i][j] = getCellValue(i, j);
            }
        }

        return result;
    }

    void Table::setCellValue(const std::string &cellIdentifier, const std::string &cellValue) {
        std::pair<unsigned long, unsigned long> rowAndCol =
                ArithmeticFormulasUtils::convertFromIdentifierToRowAndCol(cellIdentifier);
        setCellValue(rowAndCol.first, rowAndCol.second, cellValue);
    }

}

