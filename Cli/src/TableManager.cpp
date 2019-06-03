#include <iostream>
#include <iomanip>
#include <Strings.h>
#include <CsvTableFormatting.h>
#include <fstream>
#include <filesystem>
#include "TableManager.h"
#include "Log.h"
#include "Constants.h"

namespace cli {

    std::string TableManager::getPrettyTable() {
        std::stringstream stream;
        std::vector<std::vector<std::string>> cells = _table.getAllCellDisplayValues();

        if (cells.empty()) {
            stream << "Table is empty." << std::endl;
            return stream.str();
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
                stream << cells[i][j] << trailingSpaces << Constants::COLUMN_SEPARATOR;
            }
            stream << std::endl;
        }

        return stream.str();
    }

    void TableManager::edit(const std::string &cell, const std::string &cellValue) {
        core::TableCellPosition position(cell);
        _table.setCellValue(position, cellValue);
        _savedChanges = false;
    }

    void TableManager::_serialize(std::ostream &ostream) {
        std::string serialized = serialization::csv::serialize(_table);
        ostream << serialized;
    }

    void TableManager::_deserializeAndLoad(std::istream &istream) {
        core::Table table = serialization::csv::deserialize(istream);
        _table = table;
    }

    bool TableManager::areChangesSaved() const {
        return _savedChanges;
    }

    bool TableManager::isNewFile() const {
        return _currentFilePath.empty();
    }

    void TableManager::open(const std::string &filePath) {
        std::ifstream file(filePath);

        if (file.fail()) {
            throw std::invalid_argument("File could not be opened: " + filePath);
        }

        _deserializeAndLoad(file);
        _currentFilePath = filePath;
    }

    void TableManager::save() {
        if (_currentFilePath.empty()) {
            throw std::logic_error("Current file doesn't exist, so it can't be saved directly.");
        }

        std::ofstream file(_currentFilePath, std::ios::trunc);
        _serialize(file);
        file.close();
        _savedChanges = true;
    }

    void TableManager::saveAs(const std::string &savePath) {
        try {
            std::ofstream file(savePath, std::ios::trunc);
            _serialize(file);
            file.close();
            _savedChanges = true;
            _currentFilePath = savePath;
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::string TableManager::getCurrentFile() const {
        return _currentFilePath;
    }
}