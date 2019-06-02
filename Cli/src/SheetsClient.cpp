#include <algorithm>
#include <Strings.h>
#include "SheetsClient.h"
#include "Commands.h"
#include "Log.h"
#include <iostream>

namespace cli {

    SheetsClient::SheetsClient(std::ostream &ostream, std::istream &istream)
            : Client(ostream, istream), _tableManager(ostream, istream) {
        setQuitMessage("Exiting Sheets...");
    }

    void SheetsClient::onInput(const std::string &input) {
        std::string trimmed = utils::Strings::trim(input);
        std::vector<std::string> separatedInput = utils::Strings::splitBySpaces(input, 2);

        if (separatedInput.empty()) {
            return;
        }

        std::string command = separatedInput[0];
        std::string lowerCaseCmd = utils::Strings::toLowerCase(command);

        separatedInput.erase(separatedInput.begin());

        try {
            if (lowerCaseCmd == Commands::PRINT) {
                _tableManager.prettyPrint();
            } else if (lowerCaseCmd == Commands::EDIT) {
                _tableManager.edit(separatedInput);
            } else if (lowerCaseCmd == Commands::OPEN) {
                //Open
            } else if (lowerCaseCmd == Commands::SAVE) {
                //Save
            } else if (lowerCaseCmd == Commands::SAVE_AS) {
                //Save as
            } else {
                getOstream() << "Unknown command: " << command << std::endl;
            }
        } catch (const std::invalid_argument &e) {
            getOstream() << e.what() << std::endl;
        }
    }
}