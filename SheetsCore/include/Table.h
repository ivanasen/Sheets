#pragma once

#include <vector>
#include <string>
#include <memory>
#include "TableCell.h"
#include "../src/TableCellParser.h"

namespace SheetsCore {
    class Table {
    public:
        static const int DEFAULT_INITIAL_HEIGHT;
        static const int DEFAULT_INITIAL_WIDTH;

        Table();

        Table(unsigned initialHeight, unsigned initialWidth);

        std::string getCellValue(unsigned row, unsigned col) const;

        std::vector<std::vector<std::string>> getAllCellValues() const;

        void setCellValue(unsigned row, unsigned col, const std::string &cellValue);

        void setCellValue(const std::string &cellIdentifier, const std::string &cellValue);

    private:
        std::vector<std::vector<TableCell>> _cells;

        void _resizeIfNeeded(unsigned requiredHeight, unsigned requiredWidth);
    };
}
