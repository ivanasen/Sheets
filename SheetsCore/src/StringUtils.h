#pragma once

#include <string>

namespace SheetsCore {

    static void ltrim(std::string &string);

    static void rtrim(std::string &string);

    static void trim(std::string &string);

    static std::vector<std::string> splitBySpaces(const std::string &string);

    static std::vector<std::string> split(const std::string &string, char separator);

    static bool isInteger(const std::string &s);

    static bool isDecimal(const std::string &s);
}