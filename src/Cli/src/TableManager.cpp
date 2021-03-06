#include <iomanip>
#include <Strings.h>
#include <CsvFormatter.h>
#include <fstream>
#include <experimental/filesystem>
#include <Files.h>
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
        _table.setCellValue(position.getRow(), position.getColumn(), cellValue);
        _savedChanges = false;
    }

    void TableManager::serialize(std::ostream &ostream) {
        std::string serialized = serialization::CsvFormatter::serialize(_table);
        ostream << serialized;
    }

    void TableManager::deserializeAndLoad(std::istream &istream) {
        core::Table table = serialization::CsvFormatter::deserialize(istream);
        _table = table;
    }

    bool TableManager::areChangesSaved() const {
        return _savedChanges;
    }

    bool TableManager::isNewFile() const {
        return _currentFilePath.empty();
    }

    void TableManager::open(const std::string &filePath) {
        if (utils::Files::isDirectory(filePath.c_str())) {
            throw std::invalid_argument("Given path is a directory: \"" + filePath + "\"");
        }

        std::ifstream file(filePath);

        if (file.fail()) {
            throw std::invalid_argument("File doesn't exist or missing read permissions: \"" + filePath + "\"");
        }

        deserializeAndLoad(file);
        _currentFilePath = filePath;
    }

    void TableManager::save() {
        if (isNewFile()) {
            throw std::logic_error("Current file doesn't exist, so it can't be saved directly.");
        }

        std::ofstream file(_currentFilePath, std::ios::trunc);
        serialize(file);
        file.close();
        _savedChanges = true;
    }

    void TableManager::saveAs(const std::string &savePath) {
        std::ofstream file(savePath, std::ios::trunc);
        serialize(file);
        file.close();
        _savedChanges = true;
        _currentFilePath = savePath;
    }

    std::string TableManager::getCurrentFile() const {
        return _currentFilePath;
    }

    void TableManager::createNew() {
        _table = core::Table();
        _savedChanges = true;
        _currentFilePath = "";
    }
}