#pragma once

#include <string>
#include <fstream>

namespace Cli {

    class Client {
    public:
        Client();

        Client(std::string commandPrefix, std::string quitCommand, std::string quitMessage);

        virtual void start();

    protected:
        void setCommandPrefix(const std::string &cmdPrefix);

        void setQuitMessage(const std::string &quitMessage);

        std::string getCommandPrefix();

        std::string getExitMessage();

        static std::string DEFAULT_CMD_PREFIX();

        static std::string DEFAULT_QUIT_COMMAND();

        static std::string DEFAULT_QUIT_MESSAGE();

        virtual void onInput(const std::string &input) = 0;

    private:
        std::string _cmdPrefix;
        std::string _quitCmd;
        std::string _quitMsg;
    };


}