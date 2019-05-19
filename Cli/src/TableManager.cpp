#include <iostream>
#include "TableManager.h"
#include "TableUtils.h"

namespace Cli {

    void TableManager::print() {
        TableUtils::printTable(_table);
    }

    void TableManager::edit() {
        std::string cell;
        std::cout << "Enter cell number you\'d like to edit: ";
        std::cin >> cell;

        std::string newCellValue;
        std::cout << "New cell value: ";
        std::cin.ignore();
        std::getline(std::cin, newCellValue);

        try {
            _table.setCellValue(cell, newCellValue);
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

}