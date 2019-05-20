#include "Table.h"
#include "StringUtils.h"
#include "ArithmeticFormulasUtils.h"
#include "TokenValues.h"
#include "Constants.cpp"
#include "FormulaTableCell.h"
#include <iostream>

namespace SheetsCore {
    const size_t Table::DEFAULT_INITIAL_HEIGHT = 10;
    const size_t Table::DEFAULT_INITIAL_WIDTH = 10;

    std::string Table::getCellValue(size_t row, size_t col) const {
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

    Table::Table(size_t initialHeight, size_t initialWidth)
            : _cells(initialHeight, std::vector<std::shared_ptr<TableCell>>(initialWidth)) {
    }

    void Table::setCellValue(size_t row, size_t col, const std::string &newCellValue) {
        _resizeIfNeeded(row + 1, col + 1);

        CellType newCellType = _determineCellType(newCellValue);

        if (newCellType == CellType::FORMULA) {
            _cells[row][col] = std::make_shared<FormulaTableCell>(row, col, newCellValue, *this);
        } else {
            _cells[row][col] = std::make_shared<TableCell>(newCellType, newCellValue);
        }
    }

    void Table::_resizeIfNeeded(size_t requiredHeight, size_t requiredWidth) {
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
        TableCellPosition position = ArithmeticFormulasUtils::convertFromIdentifierToTablePosition(identifier);
        setCellValue(position.row, position.column, cellValue);
    }

    std::string Table::getCellValue(const std::string &identifier) const {
        TableCellPosition position = ArithmeticFormulasUtils::convertFromIdentifierToTablePosition(identifier);
        return getCellValue(position.row, position.column);
    }

    const std::shared_ptr<TableCell> Table::getCell(size_t row, size_t column) const {
        return _cells[row][column];
    }

    CellType Table::_determineCellType(const std::string &cellValue) {
        if (StringUtils::isInteger(cellValue)) {
            return CellType::INTEGER;
        } else if (StringUtils::isDecimal(cellValue)) {
            return CellType::DECIMAL;
        } else if (ArithmeticFormulasUtils::isFormula(cellValue)) {
            return CellType::FORMULA;
        } else {
            return CellType::STRING;
        }
    }
}