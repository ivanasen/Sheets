#include <algorithm>
#include <Strings.h>
#include "SheetsClient.h"
#include "Commands.h"
#include "Log.h"
#include <iostream>

namespace cli {

    void SheetsClient::onInput(const std::string &input) {
        std::string lowerInput = utils::Strings::toLowerCase(input);

        if (lowerInput == Commands::PRINT) {
            _tableManager.prettyPrint();
        } else if (lowerInput == Commands::EDIT) {
            _tableManager.edit();
        } else {
            getOstream() << "Unknown command: " << std::endl;
        }
    }

    SheetsClient::SheetsClient(std::ostream &ostream, std::istream &istream)
            : Client(ostream, istream), _tableManager(ostream, istream) {
        setQuitMessage("Exiting Sheets...");
    }
}