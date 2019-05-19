#pragma once

#include <Table.h>

namespace Cli {

    class TableManager {
    public:
        void print();

        void edit();

    private:
        SheetsCore::Table _table;
    };

}