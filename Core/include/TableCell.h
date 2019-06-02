#pragma once

#include <string>
#include "../src/CellType.h"
#include "../src/TableCellPosition.h"

namespace core {
    class TableCell {
    public:
        virtual std::string getDisplayValue() = 0;

        virtual std::string getValue() = 0;

        virtual CellType getType() const = 0;

        virtual ~TableCell() = default;
    };
}

