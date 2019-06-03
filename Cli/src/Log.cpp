#include <iostream>
#include "Log.h"

namespace cli {

    Log::Log(std::ostream &ostream, std::istream &istream)
            : _ostream(ostream), _istream(istream) {
    }

    void Log::i(const std::string &s) {
        std::cout << s << std::endl;
    }

    void Log::e(const std::string &s) {
        std::cerr << s << std::endl;
    }

}