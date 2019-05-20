#pragma once


#include <cstdio>

struct TableCellPosition {
public:
    size_t row;
    size_t column;

    TableCellPosition(size_t row, size_t column);

    bool operator==(const TableCellPosition &other) const;
};


