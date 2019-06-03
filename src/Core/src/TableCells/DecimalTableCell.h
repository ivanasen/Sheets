#pragma once

#include "TableCell.h"

namespace core {
    class DecimalTableCell : public TableCell {
    public:
        explicit DecimalTableCell(double value);

        std::string getDisplayValue() override;

        std::string getValue() override;

        double getDecimalValue() const;

        CellType getType() const override;

        TableCell *clone() override;

        ~DecimalTableCell() override;

    private:
        std::string _strValue;
        std::string _formattedValue;
        double _value;

        void formatValue();
    };

}
