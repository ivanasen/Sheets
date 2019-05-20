#pragma once

#include <string>

namespace Utils {

    class Log {
    public:
        static void i(const std::string &s);

        static void e(const std::string &s);
    };

}