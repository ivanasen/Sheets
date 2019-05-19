#pragma once

#include <string>
#include "Client.h"

namespace Cli {

    class SheetsClient : public Client {
    public:
        static void init();

    private:
        void onInput(const std::string &input) override;
    };

}
