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

    void TableManager::edit() {
        std::string cell;
        _ostream << "Enter cell number you\'d like to edit: ";
        std::getline(_istream, cell);

        try {
            core::TableCellPosition position(cell);
            std::string newCellValue;
            _ostream << "New cell value: ";
            std::getline(_istream, newCellValue);

            try {
                _table.setCellValue(position, newCellValue);
            } catch (const std::invalid_argument &e) {
                _ostream << e.what() << std::endl;
            }
        } catch (const std::invalid_argument &e) {
            _ostream << e.what() << std::endl;
        }
    }

    void TableManager::serialize(std::ostream &ostream) {
        std::string serialized = serialization::csv::serialize(_table);
        ostream << serialized;
    }

    void TableManager::deserializeAndLoad(std::istream &istream) {
        serialization::csv::deserialize(istream);
    }
}