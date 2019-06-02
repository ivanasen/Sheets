#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Strings.h"

namespace utils {

    const std::unordered_set<char> Strings::ESCAPE_CHARS = {
            '"', '\\', '\n', '\t'
    };

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

    std::string Strings::trim(std::string string) {
        ltrim(string);
        rtrim(string);
        return string;
    }

    std::vector<std::string> Strings::splitBySpaces(const std::string &string, int maxSplitAmount = -1) {
        int splitAmount = 0;
        std::vector<std::string> separated;
        auto iterator = string.begin();

        while (iterator != string.end()) {
            if (std::isspace(*iterator)) {
                iterator++;
            } else {
                std::string newElement;

                if (splitAmount == maxSplitAmount) {
                    while (iterator != string.end()) {
                        newElement.push_back(*(iterator++));
                    }
                } else {
                    while (iterator != string.end() && !std::isspace(*iterator)) {
                        newElement.push_back(*(iterator++));
                    }
                }

                separated.push_back(newElement);
                splitAmount++;
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
        std::string trimmed = trim(s);

        for (char c : trimmed) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return !trimmed.empty();
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
        return !trimmed.empty();
    }

    std::string Strings::toLowerCase(std::string string) {
        std::string copy = std::move(string);
        std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
        return copy;
    }

    std::string Strings::toUpperCase(std::string string) {
        std::string copy = std::move(string);
        std::transform(copy.begin(), copy.end(), copy.begin(), ::toupper);
        return copy;
    }

    std::string Strings::escape(const std::string &s) {
        std::string escaped;

        for (char c : s) {
            if (ESCAPE_CHARS.count(c)) {
                escaped += "\\";

                if (c == '\n') {
                    escaped += 'n';
                } else if (c == '\t') {
                    escaped += 't';
                } else {
                    escaped += c;
                }
            } else {
                escaped += c;
            }
        }

        return escaped;
    }

    std::string Strings::unescape(const std::string &s) {
        std::string unescaped;

        for (size_t i = 0; i < s.size(); i++) {

            if (s[i] == '\\' && i < s.size() - 1) {
                i++;

                switch (s[i]) {
                    case 'n':
                        unescaped += '\n';
                        break;
                    case 't':
                        unescaped += '\t';
                        break;
                    default:
                        unescaped += s[i];
                }
            } else {
                unescaped += s[i];
            }
        }

        return unescaped;
    }

    std::string Strings::addQuotes(const std::string &s) {
        return "\"" + s + "\"";
    }

    std::string Strings::removeQuotes(const std::string &s) {
        if (s.size() < 2) {
            return s;
        }

        std::string noQuotes;
        long startQuotesIndex = 0;
        bool foundStartQuotes = false;
        while (startQuotesIndex < s.size()
               && (s[startQuotesIndex] == ' '
                   || !foundStartQuotes)) {
            if (s[startQuotesIndex] == '"') {
                foundStartQuotes = true;
            } else {
                startQuotesIndex++;
            }
        }

        if (startQuotesIndex == s.size() - 1) {
            return s;
        }

        long endQuotesIndex = s.size() - 1;
        bool foundEndQuotes = false;
        while (endQuotesIndex >= 0
               && (s[endQuotesIndex] == ' '
                   || !foundEndQuotes)) {
            if (s[endQuotesIndex] == '"') {
                foundEndQuotes = true;
            } else {
                endQuotesIndex--;
            }
        }

        if (startQuotesIndex == endQuotesIndex) {
            return s;
        }

        if (foundStartQuotes && foundEndQuotes) {
            return s.substr(startQuotesIndex + 1, endQuotesIndex - startQuotesIndex - 1);
        } else {
            return s;
        }
    }

    bool Strings::ignoreCaseEquals(const std::string &a, const std::string &b) {
        return std::equal(a.begin(), a.end(),
                          b.begin(), b.end(),
                          [](char a, char b) {
                              return tolower(a) == tolower(b);
                          });
    }

    std::string Strings::formatAsDisplayDecimalValue(double value) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    }

}