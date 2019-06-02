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

    void SheetsClient::_onInput(const std::string &input) {
        std::vector<std::string> separatedInput = _separateInput(input);

        if (separatedInput.empty()) {
            return;
        }

        std::string command = separatedInput[0];
        separatedInput.erase(separatedInput.begin());
        std::string lowerCaseCmd = utils::Strings::toLowerCase(command);

        try {
            if (lowerCaseCmd == Commands::PRINT) {
                _handlePrint();
            } else if (lowerCaseCmd == Commands::EDIT) {
                _handleEdit(separatedInput);
            } else if (lowerCaseCmd == Commands::OPEN) {
                _handleOpen(separatedInput);
            } else if (lowerCaseCmd == Commands::SAVE) {
                _handleSave();
            } else if (lowerCaseCmd == Commands::SAVE_AS) {
                _handleSaveAs(separatedInput);
            } else {
                getOstream() << "Unknown command: " << command << std::endl;
            }
        } catch (const std::invalid_argument &e) {
            getOstream() << e.what() << std::endl;
        }
    }

    std::vector<std::string> SheetsClient::_separateInput(const std::string &input) {
        std::string trimmed = utils::Strings::trim(input);
        std::vector<std::string> separatedInput = utils::Strings::splitBySpaces(input, 2);
        return separatedInput;
    }

    void SheetsClient::_handlePrint() {
        _tableManager.prettyPrint();
    }

    void SheetsClient::_handleEdit(const std::vector<std::string> &input) {
        _tableManager.edit(input);
    }

    void SheetsClient::_handleOpen(const std::vector<std::string> &input) {
        //Open
    }

    void SheetsClient::_handleSave() {
        //Save
    }

    void SheetsClient::_handleSaveAs(const std::vector<std::string> &input) {
        //Save as
    }
}