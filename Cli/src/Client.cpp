#include <utility>

#include <vector>
#include <iostream>
#include "Client.h"
#include "StringUtils.h"
#include "Client.h"

namespace Cli {

    void Client::start() {
        std::string input;
        std::cout << _cmdPrefix;
        do {
            getline(std::cin, input);
            std::string trimmed = StringUtils::trimString(input);
            if (!trimmed.empty() && trimmed != _quitCmd) {
                onInput(trimmed);
            }
            std::cout << _cmdPrefix;
        } while (input != _quitCmd);

        std::cout << "Exiting the program...";
    }

    void Client::setCommandPrefix(const std::string &cmdPrefix) {
        _cmdPrefix = cmdPrefix;
    }

    std::string Client::getCommandPrefix() {
        return _cmdPrefix;
    }

    std::string Client::DEFAULT_CMD_PREFIX() {
        return "> ";
    }

    std::string Client::DEFAULT_QUIT_CMD() {
        return "exit";
    }

    Client::Client() : _cmdPrefix(DEFAULT_CMD_PREFIX()), _quitCmd(DEFAULT_QUIT_CMD()) {
    }

    Client::Client(std::string commandPrefix, std::string quitCommand)
            : _cmdPrefix(std::move(commandPrefix)), _quitCmd(std::move(quitCommand)) {
    }

}