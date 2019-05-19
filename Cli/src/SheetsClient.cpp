#include <algorithm>
#include "SheetsClient.h"
#include "StringUtils.h"
#include "Commands.h"
#include "Log.h"

namespace Cli {

    void SheetsClient::init() {
        SheetsClient client;
        client.start();
    }

    void SheetsClient::onInput(const std::string &input) {
        std::string lowerInput = StringUtils::toLowerCase(input);

        if (lowerInput == Commands::PRINT) {
            _tableManager.print();
        } else if (lowerInput == Commands::EDIT) {
            _tableManager.edit();
        } else {
            Log::i("Unknown command: " + input);
        }
    }
}