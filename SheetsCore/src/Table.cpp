#include "Table.h"
#include "TableFormulaCalculator.h"
#include "StringUtils.h"
#include "ArithmeticFormulasUtils.h"
#include "TokenValues.h"
#include "Constants.cpp"
#include "FormulaTableCell.h"
#include <iostream>

namespace SheetsCore {
    const int Table::DEFAULT_INITIAL_HEIGHT = 10;
    const int Table::DEFAULT_INITIAL_WIDTH = 10;

    std::string Table::getCellValue(unsigned row, unsigned col) const {
        if (row > _cells.size() - 1
            || (!_cells.empty() && col > _cells[0].size() - 1)
            || _cells[row][col] == nullptr) {
            return "";
        }

        try {
            return _cells[row][col]->getValue();
        } catch (const std::invalid_argument &e) {
            return ERROR_TABLE_CELL_VALUE;
        }
    }

    Table::Table(unsigned initialHeight, unsigned initialWidth)
            : _cells(initialHeight, std::vector<std::shared_ptr<TableCell>>(initialWidth)) {
    }

    void Table::setCellValue(unsigned row, unsigned col, const std::string &cellValue) {
        _resizeIfNeeded(row + 1, col + 1);

        TableCell newCell = TableCellParser::parse(cellValue);

        if (newCell.getType() == CellType::FORMULA) {
            _cells[row][col] = std::make_shared<FormulaTableCell>(newCell.getValue(), *this);
        } else {
            _cells[row][col] = std::make_shared<TableCell>(newCell);
        }
    }

    void Table::_resizeIfNeeded(unsigned requiredHeight, unsigned requiredWidth) {
        if (requiredHeight > _cells.size()) {
            _cells.resize(requiredHeight);
        }

        if ((_cells.empty() && requiredWidth > 0) || requiredWidth > _cells[0].size()) {
            for (std::vector<std::shared_ptr<TableCell>> &row : _cells) {
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

    void Table::setCellValue(const std::string &identifier, const std::string &cellValue) {
        std::pair<unsigned long, unsigned long> rowAndCol =
                ArithmeticFormulasUtils::convertFromIdentifierToRowAndCol(identifier);
        setCellValue(rowAndCol.first, rowAndCol.second, cellValue);
    }

    std::string Table::getCellValue(const std::string &identifier) const {
        std::pair<unsigned long, unsigned long> rowAndCol =
                ArithmeticFormulasUtils::convertFromIdentifierToRowAndCol(identifier);
        return getCellValue(rowAndCol.first, rowAndCol.second);
    }

    const TableCell &Table::getCell(unsigned row, unsigned col) const {
        return *_cells[row][col];
    }

}