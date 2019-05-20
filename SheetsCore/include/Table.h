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

        Table();

        Table(size_t initialHeight, size_t initialWidth);

        std::string getCellValue(size_t row, size_t col) const;

        std::string getCellValue(const std::string &identifier) const;

        const std::shared_ptr<TableCell> getCell(size_t row, size_t column) const;

        std::vector<std::vector<std::string>> getAllCellValues() const;

        void setCellValue(size_t row, size_t col, const std::string &newCellValue);

        void setCellValue(const std::string &identifier, const std::string &cellValue);

    private:
        std::vector<std::vector<std::shared_ptr<TableCell>>> _cells;

        void _resizeIfNeeded(size_t requiredHeight, size_t requiredWidth);

        static CellType _determineCellType(const std::string &cellValue);
    };
}
