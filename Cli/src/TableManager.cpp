#include <iostream>
#include <iomanip>
#include <Strings.h>
#include "TableManager.h"
#include "Log.h"
#include "Constants.h"

namespace Cli {

    void TableManager::print() {
        std::vector<std::vector<std::string>> cells = _table.getAllCellValues();

        if (cells.empty()) {
            Utils::Log::i("Table is empty.");
            return;
        }

        for (std::vector<std::string> &rows : cells) {
            for (std::string &cell : rows) {
                cell = _formatCell(cell);
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

    void TableManager::edit() {
        std::string cell;
        std::cout << "Enter cell number you\'d like to edit: ";
        std::getline(std::cin, cell);

        try {
            SheetsCore::TableCellPosition position(cell);
            std::string newCellValue;
            std::cout << "New cell value: ";
            std::getline(std::cin, newCellValue);

            try {
                _table.setCellValue(position, newCellValue);
            } catch (const std::invalid_argument &e) {
                std::cout << e.what() << std::endl;
            }
        } catch (const std::invalid_argument &e) {
            Utils::Log::i(e.what());
        }

    }

    std::string TableManager::_formatCell(const std::string &cell) {
        if (Utils::Strings::isDecimal(cell)) {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << std::stod(cell);
            return stream.str();
        }

        return cell;
    }

}