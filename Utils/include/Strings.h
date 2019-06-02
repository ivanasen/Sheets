#pragma once

#include <string>
#include <vector>
#include <unordered_set>

namespace utils {

    class Strings {
    public:
        static void ltrim(std::string &string);

        static void rtrim(std::string &string);

        static std::string trim(std::string string);

        static std::vector<std::string> splitBySpaces(const std::string &string, int maxSplitAmount = -1);

        static std::vector<std::string> split(const std::string &string, char separator);

        static bool isInteger(const std::string &s);

        static bool isDecimal(const std::string &s);

        static std::string toLowerCase(std::string string);

        static std::string toUpperCase(std::string string);

        static std::string escape(const std::string &s);

        static std::string unescape(const std::string &s);

        static std::string addQuotes(const std::string &s);

        static std::string removeQuotes(const std::string &s);

        static bool ignoreCaseEquals(const std::string &a, const std::string &b);

        static std::string formatAsDisplayDecimalValue(double value);

    private:
        static const std::unordered_set<char> ESCAPE_CHARS;
    };

}