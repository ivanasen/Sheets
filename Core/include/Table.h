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
        static const std::string EMPTY_CELL_VALUE;
        static const std::string ERROR_TABLE_CELL_VALUE;

        Table();

        Table(size_t initialHeight, size_t initialWidth);

        Table(const Table &table);

        Table &operator=(const Table &other);

        std::string getCellDisplayValue(size_t row, size_t col) const;

        const TableCell *getCell(size_t row, size_t col) const;

        std::vector<std::vector<std::string>> getAllCellDisplayValues() const;

        std::vector<std::vector<std::string>> getAllCellValues() const;

        void setCellValue(size_t row, size_t col, const std::string &newCellValue);

        size_t getHeight() const;

        size_t getWidth() const;

        ~Table();

    private:
        std::vector<std::vector<TableCell *>> _cells;

        static CellType determineCellType(const std::string &cellValue);

        void resizeIfNotBigEnough(size_t height, size_t width);

        void copy(const Table &table);

        void freeMemory();
    };
}
