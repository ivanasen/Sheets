#include "Table.h"
#include <Strings.h>
#include "ArithmeticFormulasUtils.h"
#include "TokenValues.h"
#include "FormulaTableCell.h"
#include "exceptions/TableCellRangeException.h"
#include "DecimalTableCell.h"
#include "IntegerTableCell.h"
#include "StringTableCell.h"

namespace core {
    const size_t Table::DEFAULT_INITIAL_HEIGHT = 10;
    const size_t Table::DEFAULT_INITIAL_WIDTH = 10;
    const size_t Table::MAX_SIZE = 1000;
    const std::string Table::EMPTY_CELL_VALUE = "";
    const std::string Table::ERROR_TABLE_CELL_VALUE = "Error";

    Table::Table(size_t initialHeight, size_t initialWidth)
            : _cells(initialHeight, std::vector<TableCell *>(initialWidth)) {
    }

    Table::Table() : Table(DEFAULT_INITIAL_HEIGHT, DEFAULT_INITIAL_WIDTH) {
    }

    Table::Table(const Table &table) {
        _copy(table);
    }

    Table &Table::operator=(const Table &other) {
        if (this != &other) {
            _freeMemory();
            _copy(other);
        }
        return *this;
    }

    std::string Table::getCellDisplayValue(const TableCellPosition &position) const {
        size_t row = position.getRow();
        size_t col = position.getColumn();

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

    void Table::setCellValue(const TableCellPosition &position, const std::string &newCellValue) {
        size_t row = position.getRow();
        size_t col = position.getColumn();

        _resizeIfNotBigEnough(row + 1, col + 1);

        CellType newCellType = _determineCellType(newCellValue);

        switch (newCellType) {
            case CellType::FORMULA:
                _cells[row][col] = new FormulaTableCell(newCellValue, position, *this);
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

    void Table::setCellValue(size_t row, size_t col, const std::string &newCellValue) {
        setCellValue(TableCellPosition(row, col), newCellValue);
    }

    std::vector<std::vector<std::string>> Table::getAllCellDisplayValues() const {
        std::vector<std::vector<std::string>> result(
                _cells.size(),
                std::vector<std::string>(_cells[0].size()));

        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[0].size(); j++) {
                if (_cells[i][j] != nullptr) {
                    TableCell *cell = _cells[i][j];
                    result[i][j] = cell->getDisplayValue();
                }
            }
        }

        return result;
    }

    const TableCell *Table::getCell(const TableCellPosition &position) const {
        return _cells[position.getRow()][position.getColumn()];
    }

    size_t Table::getHeight() const {
        return _cells.size();
    }

    size_t Table::getWidth() const {
        return _cells.empty() ? 0 : _cells[0].size();
    }

    Table::~Table() {
        _freeMemory();
    }

    std::vector<std::vector<std::string>> Table::getAllCellValues() const {
        std::vector<std::vector<std::string>> result(
                _cells.size(),
                std::vector<std::string>(_cells[0].size()));

        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[0].size(); j++) {
                if (_cells[i][j] != nullptr) {
                    result[i][j] = _cells[i][j]->getValue();
                }
            }
        }

        return result;
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

    CellType Table::_determineCellType(const std::string &cellValue) {
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

    void Table::_copy(const Table &table) {
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

    void Table::_freeMemory() {
        for (const std::vector<TableCell *> &rows : _cells) {
            for (TableCell *cell : rows) {
                delete cell;
            }
        }
    }
}