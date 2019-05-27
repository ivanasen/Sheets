#pragma once

#include <string>
#include "../src/CellType.h"
#include "../src/TableCellPosition.h"

namespace core {
    class TableCell {
    public:
        TableCell();

        TableCell(CellType type, std::string value);

        TableCell(const TableCell &tableCell);

        virtual std::string getValue();

        CellType getType() const;

        virtual ~TableCell() = default;

    private:
        std::string _value;
        CellType _type;
    };
}

