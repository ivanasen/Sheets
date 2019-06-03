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

    void SheetsClient::onInput(const std::string &input) {
        std::vector<std::string> separatedInput = separateInput(input);

        if (separatedInput.empty()) {
            return;
        }

        std::string command = separatedInput[0];
        separatedInput.erase(separatedInput.begin());
        std::string lowerCaseCmd = utils::Strings::toLowerCase(command);

        if (lowerCaseCmd == Commands::PRINT) {
            handlePrint();
        } else if (lowerCaseCmd == Commands::EDIT) {
            handleEdit(separatedInput);
        } else if (lowerCaseCmd == Commands::OPEN) {
            handleOpen(separatedInput);
        } else if (lowerCaseCmd == Commands::SAVE) {
            handleSave();
        } else if (lowerCaseCmd == Commands::SAVE_AS) {
            handleSaveAs(separatedInput);
        } else {
            log.i("Unknown command: " + command);
        }
    }

    std::vector<std::string> SheetsClient::separateInput(const std::string &input) {
        std::string trimmed = utils::Strings::trim(input);
        std::vector<std::string> separatedInput = utils::Strings::splitBySpaces(input, 2);
        return separatedInput;
    }

    void SheetsClient::handlePrint() {
        log.i(_tableManager.getPrettyTable());
    }

    void SheetsClient::handleEdit(const std::vector<std::string> &args) {
        if (args.size() < 2) {
            log.i("Wrong usage of edit command. "
                  "Command should be of the form \"edit R{CellRow}C{CellCol} {NewCellValue}\"");
            return;
        }

        std::string cell = args[0];
        std::string cellValue = args[1];

        try {
            _tableManager.edit(cell, cellValue);
        } catch (const std::invalid_argument &e) {
            log.i(e.what());
        }
    }

    void SheetsClient::handleOpen(const std::vector<std::string> &input) {
        if (input.size() != 1) {
            throw std::invalid_argument("Wrong usage of open command. "
                                        "Command should be of the form \"open {FilePath}\"");
        }

        try {
            std::string filePath = input[0];
            _tableManager.open(filePath);

            log.i("Successfully opened \"" + filePath + "\"");
        } catch (const std::invalid_argument &e) {
            log.i(e.what());
        }
    }

    void SheetsClient::handleSave() {
        try {
            _tableManager.save();
            log.i("Successfully saved to \"" + _tableManager.getCurrentFile() + "\"");
        } catch (const std::logic_error &e) {
            log.i(e.what());
        }
    }

    void SheetsClient::handleSaveAs(const std::vector<std::string> &input) {
        if (input.size() != 1) {
            throw std::invalid_argument("Wrong usage of saveas command. "
                                        "Command should be of the form \"saveas {FilePath}\"");
        }

        try {
            std::string filePath = input[0];
            _tableManager.saveAs(filePath);
            log.i("Successfully saved to \"" + _tableManager.getCurrentFile() + "\"");
        } catch (const std::invalid_argument &e) {
            log.i(e.what());
        }
    }

    void SheetsClient::onExit() {
        //TODO: If the file is new and the changes aren't saved ask user for a save path
        if (_tableManager.areChangesSaved() || _tableManager.isNewFile()) {
            return;
        }

        log.i("Save changes to \"" + _tableManager.getCurrentFile() + "\"? (y/n)");
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
                log.i("Invalid answer. (y/n):");
            }
        }
    }
}