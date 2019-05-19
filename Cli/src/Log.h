#pragma once

#include <string>

namespace Cli {

    class Log {
    public:
        static void i(const std::string &s);

        static void e(const std::string &s);
    };

}