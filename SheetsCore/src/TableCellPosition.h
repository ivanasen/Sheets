#pragma once


#include <cstdio>

namespace SheetsCore {

    class TableCellPosition {
    public:
        TableCellPosition(size_t row, size_t column);

        explicit TableCellPosition(std::string identifier);

        size_t getRow() const;

        size_t getColumn() const;

        bool operator==(const TableCellPosition &other) const;

    private:
        size_t _row{};
        size_t _column{};
    };

}