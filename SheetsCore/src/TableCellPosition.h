#pragma once

#include <cstdio>
#include <regex>

namespace SheetsCore {

    class TableCellPosition {
    public:
        static const std::regex TABLE_CELL_FORMAT;

        TableCellPosition(size_t row, size_t column);

        explicit TableCellPosition(std::string identifier);

        size_t getRow() const;

        static bool isTableCellIdentifier(const std::string &s);

        size_t getColumn() const;

        bool operator==(const TableCellPosition &other) const;

    private:
        size_t _row{};
        size_t _column{};
    };

}