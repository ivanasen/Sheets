#ifndef SHEETS_INTEGERTABLECELL_H
#define SHEETS_INTEGERTABLECELL_H

#include "TableCell.h"

class IntegerTableCell : public TableCell {
public:
    explicit IntegerTableCell(int value);

    std::string getValue() override;

    void setValue(std::string const &value) override;

private:
    int _value;
};

#endif //SHEETS_INTEGERTABLECELL_H
