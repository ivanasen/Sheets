#pragma once

#include <string>
#include <vector>

namespace Cli {

    class StringUtils {
    public:
        static void ltrimString(std::string &string);

        static void rtrimString(std::string &string);

        static std::string trimString(std::string &string);

        static std::vector<std::string> splitBySpaces(const std::string &string);

        static std::vector<std::string> split(const std::string &string, char separator);
    };

}