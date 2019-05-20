#include <string>
#include <vector>
#include <algorithm>
#include "Strings.h"

namespace Utils {

    void Strings::ltrim(std::string &string) {
        std::string::iterator endTrimPosition = string.begin();

        while (std::isspace(*endTrimPosition)) {
            endTrimPosition++;
        }

        string.erase(string.begin(), endTrimPosition);
    }

    void Strings::rtrim(std::string &string) {
        std::string::iterator endTrimPosition = string.end() - 1;
        while (std::isspace(*endTrimPosition)) {
            endTrimPosition--;
        }
        if (endTrimPosition < string.end()) {
            string.erase(endTrimPosition + 1, string.end());
        }
    }

    void Strings::trim(std::string &string) {
        ltrim(string);
        rtrim(string);
    }

    std::vector<std::string> Strings::splitBySpaces(const std::string &string) {
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

    std::vector<std::string> Strings::split(const std::string &string, char separator) {
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

    bool Strings::isInteger(const std::string &s) {
        std::string trimmed = s;
        trim(trimmed);

        for (char c : trimmed) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return true;
    }

    bool Strings::isDecimal(const std::string &s) {
        std::string trimmed = s;
        trim(trimmed);

        char decimalSeparator = '.';
        bool foundDecimalSeparator = false;
        for (char c : trimmed) {
            if (std::isdigit(c)) {
                continue;
            } else if (c == decimalSeparator) {
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

    std::string Strings::toLowerCase(std::string string) {
        std::string copy = std::move(string);
        std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
        return copy;
    }

}