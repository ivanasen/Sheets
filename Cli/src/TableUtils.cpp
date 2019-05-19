#include "TableUtils.h"
#include <Table.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Log.h"
#include "Constants.h"
#include "StringUtils.h"

namespace Cli {
    void TableUtils::printTable(const SheetsCore::Table &table) {
        std::vector<std::vector<std::string>> cells = table.getAllCellValues();

        if (cells.empty()) {
            Log::i("Table is empty.");
            return;
        }

        for (std::vector<std::string> &rows : cells) {
            for (std::string &cell : rows) {
                cell = formatCell(cell);
            }
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
                std::cout << cells[i][j] << trailingSpaces << Constants::COLUMN_SEPARATOR;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::string TableUtils::formatCell(const std::string &cell) {
        if (StringUtils::isDecimal(cell)) {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << std::stod(cell);
            return stream.str();
        }

        return cell;
    }

}