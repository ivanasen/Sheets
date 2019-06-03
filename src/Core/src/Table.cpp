#include "Table.h"
#include <Strings.h>
#include "ArithmeticFormulasUtils.h"
#include "TokenValues.h"
#include "exceptions/TableCellRangeException.h"
#include "TableCells/FormulaTableCell.h"
#include "TableCells/DecimalTableCell.h"
#include "TableCells/IntegerTableCell.h"
#include "TableCells/StringTableCell.h"

namespace core {
    const size_t Table::DEFAULT_INITIAL_HEIGHT = 10;
    const size_t Table::DEFAULT_INITIAL_WIDTH = 10;
    const std::string Table::EMPTY_CELL_VALUE = "";
    const std::string Table::ERROR_TABLE_CELL_VALUE = "Error";

    Table::Table(size_t initialHeight, size_t initialWidth)
            : _cells(initialHeight, std::vector<TableCell *>(initialWidth)) {
    }

    Table::Table() : Table(DEFAULT_INITIAL_HEIGHT, DEFAULT_INITIAL_WIDTH) {
    }

    Table::Table(const Table &table) {
        copy(table);
    }

    Table &Table::operator=(const Table &other) {
        if (this != &other) {
            freeMemory();
            copy(other);
        }
        return *this;
    }

    std::string Table::getCellDisplayValue(size_t row, size_t col) const {
        if (row >= _cells.size()
            || (!_cells.empty() && col >= _cells[0].size())
            || _cells[row][col] == nullptr) {
            return EMPTY_CELL_VALUE;
        }

        try {
            return _cells[row][col]->getDisplayValue();
        } catch (const std::invalid_argument &e) {
            return ERROR_TABLE_CELL_VALUE;
        }
    }

    void Table::setCellValue(size_t row, size_t col, const std::string &newCellValue) {
        resizeIfNotBigEnough(row + 1, col + 1);

        CellType newCellType = determineCellType(newCellValue);

        switch (newCellType) {
            case CellType::FORMULA:
                _cells[row][col] = new FormulaTableCell(newCellValue, TableCellPosition(row, col), *this);
                break;

            case CellType::DECIMAL:
                _cells[row][col] = new DecimalTableCell(std::stod(newCellValue));
                break;

            case CellType::INTEGER:
                _cells[row][col] = new IntegerTableCell(std::stoi(newCellValue));
                break;

            case CellType::STRING:
                _cells[row][col] = new StringTableCell(newCellValue);
                break;

            default:
                throw std::invalid_argument("Invalid cell type");
        }
    }

    std::vector<std::vector<std::string>> Table::getAllCellDisplayValues() const {
        std::vector<std::vector<std::string>> result(
                getHeight(),
                std::vector<std::string>(getWidth()));

        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[0].size(); j++) {
                result[i][j] = getCellDisplayValue(i, j);
            }
        }

        return result;
    }

    const TableCell *Table::getCell(size_t row, size_t col) const {
        return _cells[row][col];
    }

    size_t Table::getHeight() const {
        return _cells.size();
    }

    size_t Table::getWidth() const {
        return _cells.empty() ? 0 : _cells[0].size();
    }

    Table::~Table() {
        freeMemory();
    }

    std::vector<std::vector<std::string>> Table::getAllCellValues() const {
        std::vector<std::vector<std::string>> result(
                getHeight(),
                std::vector<std::string>(getWidth()));

        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[0].size(); j++) {
                if (_cells[i][j] != nullptr) {
                    result[i][j] = _cells[i][j]->getValue();
                }
            }
        }

        return result;
    }

    void Table::resizeIfNotBigEnough(size_t height, size_t width) {
        if (height > _cells.size()) {
            _cells.resize(height);
        }

        if ((_cells.empty() && width > 0) || width > _cells[0].size()) {
            for (std::vector<TableCell *> &row : _cells) {
                row.resize(width);
            }
        }
    }

    CellType Table::determineCellType(const std::string &cellValue) {
        if (utils::Strings::isInteger(cellValue)) {
            return CellType::INTEGER;
        } else if (utils::Strings::isDecimal(cellValue)) {
            return CellType::DECIMAL;
        } else if (ArithmeticFormulasUtils::isFormula(cellValue)) {
            return CellType::FORMULA;
        } else {
            return CellType::STRING;
        }
    }

    void Table::copy(const Table &table) {
        _cells = std::vector<std::vector<TableCell *>>(
                table.getHeight(),
                std::vector<TableCell *>(table.getWidth()));
        std::vector<std::vector<TableCell *>> copiedCells = table._cells;

        for (size_t i = 0; i < table.getHeight(); i++) {
            for (size_t j = 0; j < table.getWidth(); j++) {
                if (copiedCells[i][j] != nullptr) {
                    if (copiedCells[i][j]->getType() == CellType::FORMULA) {
                        std::string formula = copiedCells[i][j]->getValue();
                        _cells[i][j] = new FormulaTableCell(
                                formula,
                                TableCellPosition(i, j),
                                *this);
                    } else {
                        _cells[i][j] = copiedCells[i][j]->clone();
                    }
                }
            }
        }
    }

    void Table::freeMemory() {
        for (const std::vector<TableCell *> &rows : _cells) {
            for (TableCell *cell : rows) {
                delete cell;
            }
        }
    }
}