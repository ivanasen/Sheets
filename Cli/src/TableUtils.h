#pragma once

#include <Table.h>

namespace Cli {
    class TableUtils {
    public:
        static void printTable(const SheetsCore::Table &table);

        static std::string formatCell(const std::string &cell);
    };
}

