#include "Table.h"
#include <Strings.h>
#include "ArithmeticFormulasUtils.h"
#include "TokenValues.h"
#include "FormulaTableCell.h"
#include "exceptions/TableCellRangeException.h"

namespace core {
    const size_t Table::DEFAULT_INITIAL_HEIGHT = 10;
    const size_t Table::DEFAULT_INITIAL_WIDTH = 10;
    const size_t Table::MAX_SIZE = 1000;
    const std::string Table::EMPTY_CELL_VALUE = "";
    const std::string Table::ERROR_TABLE_CELL_VALUE = "Error";

    std::string Table::getCellValue(const TableCellPosition &position) const {
        size_t row = position.getRow();
        size_t col = position.getColumn();

        if (row >= _cells.size()
            || (!_cells.empty() && col >= _cells[0].size())
            || _cells[row][col] == nullptr) {
            return EMPTY_CELL_VALUE;
        }

        try {
            return _cells[row][col]->getValue();
        } catch (const std::invalid_argument &e) {
            return ERROR_TABLE_CELL_VALUE;
        }
    }

    Table::Table(size_t initialHeight, size_t initialWidth)
            : _cells(initialHeight, std::vector<TableCell *>(initialWidth)) {
    }

    void Table::setCellValue(const TableCellPosition &position, const std::string &newCellValue) {
        size_t row = position.getRow();
        size_t col = position.getColumn();

        _resizeIfNotBigEnough(row + 1, col + 1);

        CellType newCellType = _determineCellType(newCellValue);

        if (newCellType == CellType::FORMULA) {
            _cells[row][col] = new FormulaTableCell(row, col, newCellValue, *this);
        } else {
            _cells[row][col] = new TableCell(newCellType, newCellValue);
        }
    }

    void Table::_resizeIfNotBigEnough(size_t height, size_t width) {
        if (height > MAX_SIZE || width > MAX_SIZE) {
            throw TableCellRangeException();
        }

        if (height > _cells.size()) {
            _cells.resize(height);
        }

        if ((_cells.empty() && width > 0) || width > _cells[0].size()) {
            for (std::vector<TableCell *> &row : _cells) {
                row.resize(width);
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
                result[i][j] = getCellValue(TableCellPosition(i, j));
            }
        }

        return result;
    }

    const TableCell *Table::getCell(const TableCellPosition &position) const {
        return _cells[position.getRow()][position.getColumn()];
    }

    CellType Table::_determineCellType(const std::string &cellValue) {
        if (Utils::Strings::isInteger(cellValue)) {
            return CellType::INTEGER;
        } else if (Utils::Strings::isDecimal(cellValue)) {
            return CellType::DECIMAL;
        } else if (ArithmeticFormulasUtils::isFormula(cellValue)) {
            return CellType::FORMULA;
        } else {
            return CellType::STRING;
        }
    }

    size_t Table::getHeight() const {
        return _cells.size();
    }

    size_t Table::getWidth() const {
        return _cells.empty() ? 0 : _cells[0].size();
    }

    Table::~Table() {
        for (const std::vector<TableCell *> &rows : _cells) {
            for (TableCell *cell : rows) {
                delete cell;
            }
        }
    }

    std::vector<std::vector<std::string>> Table::getAllCellValuesWithoutFormulaCalculations() const {
        std::vector<std::vector<std::string>> result(
                _cells.size(),
                std::vector<std::string>(_cells[0].size()));

        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[0].size(); j++) {
                if (_cells[i][j] != nullptr && _cells[i][j]->getType() == CellType::FORMULA) {
                    result[i][j] = ((FormulaTableCell *) _cells[i][j])->getFormula();
                } else {
                    result[i][j] = getCellValue(TableCellPosition(i, j));
                }
            }
        }

        return result;
    }
}