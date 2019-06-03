#pragma once

#include <string>
#include <fstream>

namespace cli {

    class Client {
    public:
        Client(std::ostream &ostream, std::istream &istream);

        Client(std::ostream &ostream,
               std::istream &istream,
               std::string commandPrefix,
               std::string quitCommand,
               std::string quitMessage);

        virtual void start();

    protected:
        void setCommandPrefix(const std::string &cmdPrefix);

        void setQuitMessage(const std::string &quitMessage);

        std::string getCommandPrefix();

        std::string getExitMessage();

        static std::string DEFAULT_CMD_PREFIX();

        static std::string DEFAULT_QUIT_COMMAND();

        static std::string DEFAULT_QUIT_MESSAGE();

        virtual void _onInput(const std::string &input) = 0;

        virtual void _onExit() = 0;

        std::ostream &getOstream();

        std::istream &getIstream();

    private:
        std::string _cmdPrefix;
        std::string _quitCmd;
        std::string _quitMsg;

        std::ostream &_ostream;
        std::istream &_istream;
    };


}