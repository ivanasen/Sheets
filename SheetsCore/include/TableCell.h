#ifndef SHEETS_TABLECELL_H
#define SHEETS_TABLECELL_H


class TableCell {
public:
    virtual std::string getValue() = 0;

    virtual void setValue(std::string const &value) = 0;
};


#endif //SHEETS_TABLECELL_H
