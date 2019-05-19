#pragma once

#include <string>
#include <Table.h>

namespace SheetsCore {

    class TableFormula {
    public:
        TableFormula(std::string formula, const Table &table);

        double calculate();

        std::string getValue();

    private:

    };

}