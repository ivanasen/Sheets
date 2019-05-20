#pragma once

#include <string>
#include "../src/CellType.h"
#include "../src/TableCellPosition.h"

namespace SheetsCore {
    class TableCell {
    public:
        TableCell();

        explicit TableCell(size_t tableRow, size_t tableColumn, CellType type, std::string value);

        TableCell(const TableCell &tableCell);

        virtual std::string getValue();

        TableCellPosition getTablePosition() const;

        CellType getType() const;

        virtual ~TableCell() = default;

    private:
        TableCellPosition _tablePosition;
        std::string _value;
        CellType _type;
    };
}

