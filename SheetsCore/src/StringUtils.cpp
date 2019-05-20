#include <string>
#include <vector>
#include "TokenType.h"
#include "Token.h"
#include "TokenValues.h"
#include "Constants.cpp"
#include "ArithmeticFormulasUtils.h"
#include "StringUtils.h"

namespace SheetsCore {

    void StringUtils::ltrim(std::string &string) {
        std::string::iterator endTrimPosition = string.begin();

        while (std::isspace(*endTrimPosition)) {
            endTrimPosition++;
        }

        string.erase(string.begin(), endTrimPosition);
    }

    void StringUtils::rtrim(std::string &string) {
        std::string::iterator endTrimPosition = string.end() - 1;
        while (std::isspace(*endTrimPosition)) {
            endTrimPosition--;
        }
        if (endTrimPosition < string.end()) {
            string.erase(endTrimPosition + 1, string.end());
        }
    }

    void StringUtils::trim(std::string &string) {
        ltrim(string);
        rtrim(string);
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

    bool StringUtils::isInteger(const std::string &s) {
        std::string trimmed = s;
        trim(trimmed);

        for (char c : trimmed) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return true;
    }

    bool StringUtils::isDecimal(const std::string &s) {
        std::string trimmed = s;
        trim(trimmed);

        Token decimalSeparator = TOKEN_VALUES[(int) TokenType::DECIMAL_SEPARATOR];
        bool foundDecimalSeparator = false;
        for (char c : trimmed) {
            if (std::isdigit(c)) {
                continue;
            } else if (std::string(1, c) == decimalSeparator.value) {
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