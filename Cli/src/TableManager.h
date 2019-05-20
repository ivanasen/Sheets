#pragma once

#include <Table.h>

namespace Cli {

    class TableManager {
    public:
        void print();

        void edit();

    private:
        SheetsCore::Table _table;

        void _printTable(const SheetsCore::Table &table);

        static std::string _formatCell(const std::string &cellValue);
    };

}