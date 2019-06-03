#pragma once

#include "TableCell.h"

namespace core {
    class IntegerTableCell : public TableCell {
    public:
        explicit IntegerTableCell(int value);

        std::string getDisplayValue() override;

        std::string getValue() override;

        int getIntValue() const;

        TableCell *clone() override;

        CellType getType() const override;

        ~IntegerTableCell() override;

    private:
        std::string _strValue;
        int _value;
    };
}

