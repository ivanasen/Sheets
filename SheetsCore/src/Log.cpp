#include <iostream>
#include "Log.h"

void Log::i(const std::string &s) {
    std::cout << s << std::endl;
}

void Log::e(const std::string &s) {
    std::cerr << s << std::endl;
}
