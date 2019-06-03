#pragma once

#include <Table.h>

namespace cli {

    class TableManager {
    public:
        std::string getPrettyTable();

        void edit(const std::string &cell, const std::string &cellValue);

        bool areChangesSaved() const;

        void open(const std::string& filePath);

        void save();

        void saveAs(const std::string &savePath);

        std::string getCurrentFile() const;

        bool isNewFile() const;

    private:
        core::Table _table;
        bool _savedChanges;
        std::string _currentFilePath;

        void _serialize(std::ostream &ostream);

        void _deserializeAndLoad(std::istream &istream);
    };

}