#pragma once

#include <string>
#include "../src/CellType.h"
#include "../src/TableCellPosition.h"

namespace SheetsCore {
    class TableCell {
    public:
        TableCell();

        explicit TableCell(CellType type, std::string value);

        TableCell(const TableCell &tableCell);

        virtual std::string getValue();

        CellType getType() const;

        virtual ~TableCell() = default;

    private:
        std::string _value;
        CellType _type;
    };
}

