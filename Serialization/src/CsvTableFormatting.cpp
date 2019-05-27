#include <string>
#include <Strings.h>
#include "CsvTableFormatting.h"

namespace serialization::csv {
    core::Table deserialize(std::istream &stream) {
        core::Table table;

        size_t tableRow = 0;
        std::string line;

        while (std::getline(stream, line)) {
            std::vector<std::string> split = utils::Strings::split(line, ',');
            for (size_t tableCol = 0; tableCol < split.size(); tableCol++) {
                core::TableCellPosition position(tableRow, tableCol);
                table.setCellValue(position, split[tableCol]);
            }
            tableRow++;
        }

        return table;
    }

    core::Table deserialize(std::string &serialized) {
        std::stringstream s(serialized);
        return deserialize(s);
    }

    void serialize(std::ostream &stream, const core::Table &table) {
        stream << serialize(table);
    }

    std::string serialize(const core::Table &table) {
        std::vector<std::vector<std::string>> cells =
                table.getAllCellValuesWithoutFormulaCalculations();

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