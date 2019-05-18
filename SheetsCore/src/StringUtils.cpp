#include <string>

static void ltrim(std::string &string) {
    std::string::iterator endTrimPosition = string.begin();

    while (std::isspace(*endTrimPosition)) {
        endTrimPosition++;
    }

    string.erase(string.begin(), endTrimPosition);
}

static void rtrim(std::string &string) {
    std::string::iterator endTrimPosition = string.end() - 1;
    while (std::isspace(*endTrimPosition)) {
        endTrimPosition--;
    }
    if (endTrimPosition < string.end()) {
        string.erase(endTrimPosition + 1, string.end());
    }
}

static void trim(std::string &string) {
    ltrim(string);
    rtrim(string);
}