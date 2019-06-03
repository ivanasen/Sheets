#pragma once

#include <string>
#include <Table.h>
#include <Token.h>

namespace serialization {

    class CsvFormatter {
    public:
        static core::Table deserialize(std::istream &istream);

        static std::string serialize(const core::Table &table);

    private:
        static std::string extractNextCellElement(std::istream &istream, char currentChar);

        static std::vector<core::Token> tokenizeSerializedTable(std::istream &istream);

        static core::Table parseTable(const std::vector<core::Token> &tokens);
    };

}
