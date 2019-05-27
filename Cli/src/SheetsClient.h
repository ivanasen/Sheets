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

        void onInput(const std::string &input) override;
    };

}
