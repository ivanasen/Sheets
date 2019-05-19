#include <utility>

#include <string>
#include <vector>
#include <algorithm>
#include "StringUtils.h"
#include "Constants.h"

namespace Cli {

    void StringUtils::ltrimString(std::string &string) {
        std::string::iterator endTrimPosition = string.begin();

        while (std::isspace(*endTrimPosition)) {
            endTrimPosition++;
        }

        string.erase(string.begin(), endTrimPosition);
    }

    void StringUtils::rtrimString(std::string &string) {
        std::string::iterator endTrimPosition = string.end() - 1;
        while (std::isspace(*endTrimPosition)) {
            endTrimPosition--;
        }
        if (endTrimPosition < string.end()) {
            string.erase(endTrimPosition + 1, string.end());
        }
    }

    std::string StringUtils::trimString(std::string &string) {
        std::string trimmed = string;
        ltrimString(trimmed);
        rtrimString(trimmed);
        return trimmed;
    }

    std::vector<std::string> StringUtils::splitBySpaces(const std::string &string) {
        std::vector<std::string> separated;
        auto iterator = string.begin();

        while (iterator != string.end()) {
            if (std::isspace(*iterator)) {
                iterator++;
            } else {
                std::string newElement;
                while (iterator != string.end() && !std::isspace(*iterator)) {
                    newElement.push_back(*(iterator++));
                }
                separated.push_back(newElement);
            }
        }

        return separated;
    }

    std::vector<std::string> StringUtils::split(const std::string &string, char separator) {
        std::vector<std::string> separated;
        auto iterator = string.begin();

        while (iterator != string.end()) {
            if (*iterator == separator) {
                iterator++;
            } else {
                std::string newElement;
                while (iterator != string.end() && *iterator != separator) {
                    newElement.push_back(*iterator++);
                }
                separated.push_back(newElement);
            }
        }

        return separated;
    }

    std::string StringUtils::toLowerCase(std::string string) {
        std::string copy = std::move(string);
        std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
        return copy;
    }

    bool StringUtils::isDecimal(const std::string &s) {
        std::string trimmed = s;
        StringUtils::trimString(trimmed);

        std::string decimalSeparator = Constants::DECIMAL_SEPARATOR;
        bool foundDecimalSeparator = false;
        for (char c : trimmed) {
            if (std::isdigit(c)) {
                continue;
            } else if (std::string(1, c) == decimalSeparator) {
                if (foundDecimalSeparator) {
                    return false;
                }
                foundDecimalSeparator = true;
            } else {
                return false;
            }
        }
        return !s.empty();
    }

}