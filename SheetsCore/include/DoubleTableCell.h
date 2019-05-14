#pragma once

#include <string>
#include "TableCell.h"

class DoubleTableCell : public TableCell {
public:
    explicit DoubleTableCell(double value);

    std::string getValue() override;

    void setValue(const std::string &value) override;

private:
    double _value;
};