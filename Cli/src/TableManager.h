#pragma once

#include <Table.h>

namespace cli {

    class TableManager {
    public:
        TableManager(std::ostream &ostream, std::istream &istream);

        void prettyPrint();

        void edit();

        void serialize(std::ostream &ostream);

        void deserializeAndLoad(std::istream &istream);

    private:
        core::Table _table;
        std::ostream &_ostream;
        std::istream &_istream;

        static std::string _formatCell(const std::string &cellValue);
    };

}