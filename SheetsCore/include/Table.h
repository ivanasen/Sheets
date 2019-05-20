#pragma once

#include <vector>
#include <string>
#include <memory>
#include "TableCell.h"

namespace SheetsCore {
    class Table {
    public:
        static const size_t DEFAULT_INITIAL_HEIGHT;
        static const size_t DEFAULT_INITIAL_WIDTH;
        static const size_t MAX_SIZE;

        Table();

        Table(size_t initialHeight, size_t initialWidth);

        std::string getCellValue(const TableCellPosition &position) const;

        const std::shared_ptr<TableCell> getCell(const TableCellPosition &position) const;

        std::vector<std::vector<std::string>> getAllCellValues() const;

        void setCellValue(const TableCellPosition &position, const std::string &newCellValue);

        size_t getHeight() const;

        size_t getWidth() const;

    private:
        std::vector<std::vector<std::shared_ptr<TableCell>>> _cells;

        void _resizeIfNeeded(size_t requiredHeight, size_t requiredWidth);

        static CellType _determineCellType(const std::string &cellValue);
    };
}
