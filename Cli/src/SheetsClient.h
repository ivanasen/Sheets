#pragma once

#include <string>
#include "TableManager.h"
#include "Client.h"

namespace cli {

    class SheetsClient : public Client {
    public:
        SheetsClient(std::ostream &ostream, std::istream &istream);

    private:
        TableManager _tableManager;

        void _onInput(const std::string &input) override;

        void _handlePrint();

        void _handleEdit(const std::vector<std::string>& input);

        static std::vector<std::string> _separateInput(const std::string &input);

        void _handleOpen(const std::vector<std::string>& input);

        void _handleSave();

        void _handleSaveAs(const std::vector<std::string>& input);
    };

}
