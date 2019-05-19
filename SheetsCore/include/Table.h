#pragma once

#include <vector>
#include <string>
#include <memory>
#include "TableCell.h"
#include "../src/TableCellParser.h"

namespace SheetsCore {
    class Table {
    public:
        static const int DEFAULT_INITIAL_HEIGHT = 10;
        static const int DEFAULT_INITIAL_WIDTH = 10;

        Table();

        Table(unsigned initialHeight, unsigned initialWidth);

        std::string getCellValue(unsigned row, unsigned col) const;

        void setCellValue(unsigned row, unsigned col, const std::string &cellValue);

    private:
        std::vector<std::vector<TableCell>> _tableValues;

        void _resizeIfNeeded(unsigned requiredHeight, unsigned requiredWidth);
    };
}
