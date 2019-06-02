#pragma once

#include <Table.h>

namespace cli {

    class TableManager {
    public:
        TableManager(std::ostream &ostream, std::istream &istream);

        void prettyPrint();

        void edit(const std::vector<std::string> &args);

        void serialize(std::ostream &ostream);

        void deserializeAndLoad(std::istream &istream);

    private:
        core::Table _table;
        std::ostream &_ostream;
        std::istream &_istream;
    };

}