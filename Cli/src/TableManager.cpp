#include <iostream>
#include "TableManager.h"
#include "TableUtils.h"
#include "../../SheetsCore/src/ArithmeticFormulasUtils.h"
#include "Log.h"

namespace Cli {

    void TableManager::print() {
        TableUtils::printTable(_table);
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
            Log::i(e.what());
        }

    }

}