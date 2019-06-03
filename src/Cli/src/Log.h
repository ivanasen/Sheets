#pragma once

#include <string>

namespace cli {

    class Log {
    public:
        Log(std::ostream &ostream, std::istream &istream);

        void i(const std::string &s);

        void e(const std::string &s);

    private:
        std::ostream &_ostream;
        std::istream &_istream;
    };

}