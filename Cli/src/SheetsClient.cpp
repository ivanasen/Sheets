#include <algorithm>
#include <Strings.h>
#include "SheetsClient.h"
#include "Commands.h"
#include "Log.h"
#include <filesystem>
#include <iostream>

namespace cli {

    SheetsClient::SheetsClient(std::ostream &ostream, std::istream &istream)
            : Client(ostream, istream) {
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
        getOstream() << _tableManager.getPrettyTable();
    }

    void SheetsClient::_handleEdit(const std::vector<std::string> &args) {
        if (args.size() < 2) {
            throw std::invalid_argument(
                    "Wrong usage of edit command. "
                    "Command should be of the form \"edit R{CellRow}C{CellCol} {NewCellValue}\"");
        }

        std::string cell = args[0];
        std::string cellValue = args[1];

        _tableManager.edit(cell, cellValue);
    }

    void SheetsClient::_handleOpen(const std::vector<std::string> &input) {
        if (input.size() != 1) {
            throw std::invalid_argument("Wrong usage of open command. "
                                        "Command should be of the form \"open {FilePath}\"");
        }

        std::string filePath = input[0];
        _tableManager.open(filePath);

        getOstream() << "Successfully opened \"" << filePath << "\"" << std::endl;
    }

    void SheetsClient::_handleSave() {
        try {
            _tableManager.save();
            getOstream() << "Successfully saved to \"" << _tableManager.getCurrentFile() << "\"" << std::endl;
        } catch (const std::logic_error &e) {
            getOstream() << e.what() << std::endl;
        }
    }

    void SheetsClient::_handleSaveAs(const std::vector<std::string> &input) {
        if (input.size() != 1) {
            throw std::invalid_argument("Wrong usage of saveas command. "
                                        "Command should be of the form \"saveas {FilePath}\"");
        }

        std::string filePath = input[0];
        _tableManager.saveAs(filePath);
        getOstream() << "Successfully saved to \"" << _tableManager.getCurrentFile() << "\"" << std::endl;
    }

    void SheetsClient::_onExit() {
        //TODO: If the file is new and the changes aren't saved ask user for a save path
        if (_tableManager.areChangesSaved() || _tableManager.isNewFile()) {
            return;
        }

        getOstream() << "Save changes to \"" << _tableManager.getCurrentFile() << "\"? (y/n)\n";
        bool answered = false;
        while (!answered) {
            std::string answer;
            getIstream() >> answer;

            if (answer == "y" || answer == "yes") {
                answered = true;
                _tableManager.save();
            } else if (answer == "n" || answer == "no") {
                answered = true;
            } else {
                getOstream() << "Invalid answer. (y/n):\n";
            }
        }
    }
}