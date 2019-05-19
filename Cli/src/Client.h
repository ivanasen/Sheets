#pragma once

#include <string>
#include <fstream>

namespace Cli {

    class Client {
    private:
        std::string _cmdPrefix;
        std::string _quitCmd;
    protected:
        void setCommandPrefix(const std::string &cmdPrefix);

        std::string getCommandPrefix();

        static std::string DEFAULT_CMD_PREFIX();

        static std::string DEFAULT_QUIT_CMD();

        virtual void onInput(const std::string &input) = 0;

    public:
        Client();

        Client(std::string commandPrefix, std::string quitCommand);

        virtual void start();
    };

}