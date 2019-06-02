#pragma once

#include <Table.h>

namespace cli {

    class TableManager {
    public:
        std::string getPrettyTable();

        void edit(const std::vector<std::string> &args);

        void serialize(std::ostream &ostream);

        void deserializeAndLoad(std::istream &istream);

    private:
        core::Table _table;
    };

}