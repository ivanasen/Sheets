#include <utility>

#include <vector>
#include <iostream>
#include <Strings.h>
#include "Client.h"
#include "Client.h"

namespace cli {

    Client::Client(std::ostream &ostream, std::istream &istream)
            : Client(ostream,
                     istream,
                     DEFAULT_CMD_PREFIX(),
                     DEFAULT_QUIT_COMMAND(),
                     DEFAULT_QUIT_MESSAGE()) {
    }

    Client::Client(
            std::ostream &ostream,
            std::istream &istream,
            std::string commandPrefix,
            std::string quitCommand,
            std::string quitMessage)
            : _ostream(ostream),
              _istream(istream),
              log(ostream, istream),
              _cmdPrefix(std::move(commandPrefix)),
              _quitCmd(std::move(quitCommand)),
              _quitMsg(std::move(quitMessage)) {
    }

    void Client::start() {
        std::string input;
        _ostream << _cmdPrefix;
        do {
            getline(_istream, input);
            input = utils::Strings::trim(input);
            if (!input.empty() && input != _quitCmd) {
                onInput(input);
            }
            _ostream << _cmdPrefix;
        } while (input != _quitCmd);

        onExit();

        _ostream << _quitMsg << std::endl;
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

    std::string Client::DEFAULT_QUIT_COMMAND() {
        return "exit";
    }

    std::string Client::DEFAULT_QUIT_MESSAGE() {
        return "Exiting the program...";
    }

    void Client::setQuitMessage(const std::string &quitMessage) {
        _quitMsg = quitMessage;
    }

    std::string Client::getExitMessage() {
        return _quitMsg;
    }

    std::ostream &Client::getOstream() {
        return _ostream;
    }

    std::istream &Client::getIstream() {
        return _istream;
    }

}