#include <string>
#include "CsvTableFormatting.h"

namespace serialization::csv {
    core::Table deserialize(std::istream &stream) {
        return core::Table();
    }

    core::Table deserialize(std::string &string) {
        return core::Table();
    }

    void serialize(std::ostream &stream, const core::Table &table) {
        stream << serialize(table);
    }

    std::string serialize(const core::Table &table) {
        std::vector<std::vector<std::string>> cells = table.getAllCellValuesWithoutFormulaCalculations();

        std::string serialized;

        for (const std::vector<std::string> &row : cells) {
            for (const std::string &cell : row) {
                serialized += cell + ",";
            }
            serialized += "\n";
        }

        return serialized;
    }
}