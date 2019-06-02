#include <iostream>
#include <iomanip>
#include <Strings.h>
#include <CsvTableFormatting.h>
#include "TableManager.h"
#include "Log.h"
#include "Constants.h"

namespace cli {

    TableManager::TableManager(std::ostream &ostream, std::istream &istream)
            : _ostream(ostream), _istream(istream) {
    }

    void TableManager::prettyPrint() {
        std::vector<std::vector<std::string>> cells = _table.getAllCellDisplayValues();

        if (cells.empty()) {
            _ostream << "Table is empty." << std::endl;
            return;
        }

        std::vector<unsigned long> columnSizes(cells[0].size());

        for (size_t col = 0; col < cells[0].size(); col++) {
            for (auto &row : cells) {
                if (row[col].length() > columnSizes[col]) {
                    columnSizes[col] = row[col].length();
                }
            }
        }

        for (size_t i = 0; i < cells.size(); i++) {
            for (size_t j = 0; j < cells[0].size(); j++) {
                auto trailingSpacesCount = columnSizes[j] - cells[i][j].length() + 1;
                std::string trailingSpaces = std::string(trailingSpacesCount, ' ');
                _ostream << cells[i][j] << trailingSpaces << Constants::COLUMN_SEPARATOR;
            }
            _ostream << std::endl;
        }
        _ostream << std::endl;
    }

    void TableManager::edit(const std::vector<std::string> &args) {
        if (args.size() < 2) {
            throw std::invalid_argument(
                    "Wrong usage of edit command. "
                    "Command should be of the form \"edit R{CellRow}C{CellCol} NewCellValue\"");
        }

        std::string cell = args[0];
        std::string cellValue = args[1];

        core::TableCellPosition position(cell);
        _table.setCellValue(position, cellValue);
    }

    void TableManager::serialize(std::ostream &ostream) {
        std::string serialized = serialization::csv::serialize(_table);
        ostream << serialized;
    }

    void TableManager::deserializeAndLoad(std::istream &istream) {
        serialization::csv::deserialize(istream);
    }
}