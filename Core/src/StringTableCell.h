#pragma once

#include "TableCell.h"

namespace core {

    class StringTableCell : public TableCell {
    public:
        explicit StringTableCell(const std::string &value);

        std::string getDisplayValue() override;

        std::string getValue() override;

        CellType getType() const override;

        ~StringTableCell() override;

    private:
        std::string _value;
        std::string _escapedValue;
    };

}
