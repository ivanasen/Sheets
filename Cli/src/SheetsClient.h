#pragma once

#include <string>
#include "TableManager.h"
#include "Client.h"

namespace Cli {

    class SheetsClient : public Client {
    public:
        SheetsClient();

        static void init();

    private:
        TableManager _tableManager;

        void onInput(const std::string &input) override;
    };

}
