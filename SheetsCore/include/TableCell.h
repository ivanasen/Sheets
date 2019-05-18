#pragma once

#include <string>
#include "../src/CellType.h"

class TableCell {
public:
    TableCell();

    explicit TableCell(CellType type, std::string value);

    std::string getValue() const;

    CellType getType() const;

private:
    std::string _value;
    CellType _type;
};