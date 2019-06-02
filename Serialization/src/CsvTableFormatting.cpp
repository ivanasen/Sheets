#include <string>
#include <Strings.h>
#include "CsvTableFormatting.h"

namespace serialization::csv {

    core::Table deserialize(std::istream &stream) {
        core::Table table;

        size_t tableRow = 0;
        size_t tableCol = 0;

        size_t streamRow = 0;
        size_t streamCol = 0;

        char c;
        while (stream.get(c)) {
            if (c == ',') {
                tableCol++;
                streamCol++;
            } else if (c == '\n') {
                tableRow++;
                tableCol = 0;

                streamRow++;
                streamCol = 0;
            } else if (c == ' ') {
                streamCol++;
            } else {
                std::string extracted = extract(stream, c);
                std::string unescaped = utils::Strings::removeQuotes(utils::Strings::unescape(extracted));
                table.setCellValue(core::TableCellPosition(tableRow, tableCol), unescaped);
                tableCol++;
            }
        }

        return table;
    }

    std::string extract(std::istream &istream, char previousChar) {
        char currentChar = previousChar;
        std::string result(1, currentChar);

        bool isReadingString = currentChar == '\"';
        bool isEscaped = false;
        while (istream.get(currentChar) && (isReadingString || currentChar != ',')) {
            if (currentChar == '\"' && !isEscaped) {
                isReadingString = false;
            } else {
                isEscaped = currentChar == '\\';
            }
            result += currentChar;
        }

        return result;
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
                table.getAllCellValues();

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