#pragma once

#include <string>

namespace utils {

    class Log {
    public:
        static void i(const std::string &s);

        static void e(const std::string &s);
    };

}