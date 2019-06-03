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

        void handlePrint();

        void handleEdit(const std::vector<std::string> &args);

        static std::vector<std::string> separateInput(const std::string &input);

        void handleOpen(const std::vector<std::string> &input);

        void handleSave();

        void handleSaveAs(const std::vector<std::string> &input);

    protected:

        void onInput(const std::string &input) override;

        void onExit() override;

        void checkForUnsavedFile();

        void handleClose();
    };

}
