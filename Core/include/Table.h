#pragma once

#include <vector>
#include <string>
#include <memory>
#include "TableCell.h"

namespace core {
    class Table {
    public:
        static const size_t DEFAULT_INITIAL_HEIGHT;
        static const size_t DEFAULT_INITIAL_WIDTH;
        static const size_t MAX_SIZE;
        static const std::string EMPTY_CELL_VALUE;
        static const std::string ERROR_TABLE_CELL_VALUE;

        Table();

        Table(size_t initialHeight, size_t initialWidth);

        std::string getCellValue(const TableCellPosition &position) const;

        const TableCell *getCell(const TableCellPosition &position) const;

        std::vector<std::vector<std::string>> getAllCellValues() const;

        std::vector<std::vector<std::string>> getAllCellValuesWithoutFormulaCalculations() const;

        void setCellValue(const TableCellPosition &position, const std::string &newCellValue);

        size_t getHeight() const;

        size_t getWidth() const;

        ~Table();

    private:
        std::vector<std::vector<TableCell *>> _cells;

        static CellType _determineCellType(const std::string &cellValue);

        void _resizeIfNotBigEnough(size_t height, size_t width);

    };
}
