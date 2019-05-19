#include <string>
#include <vector>
#include "StringUtils.h"

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

}