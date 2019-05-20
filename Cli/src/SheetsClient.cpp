#include <algorithm>
#include <Strings.h>
#include "SheetsClient.h"
#include "Commands.h"
#include "Log.h"

namespace Cli {

    void SheetsClient::init() {
        SheetsClient client;
        client.start();
    }

    void SheetsClient::onInput(const std::string &input) {
        std::string lowerInput = Utils::Strings::toLowerCase(input);

        if (lowerInput == Commands::PRINT) {
            _tableManager.print();
        } else if (lowerInput == Commands::EDIT) {
            _tableManager.edit();
        } else {
            Utils::Log::i("Unknown command: " + input);
        }
    }

    SheetsClient::SheetsClient() : Client() {
        setQuitMessage("Exiting Sheets...");
    }
}