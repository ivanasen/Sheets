#include <sys/stat.h>

#include "Files.h"

namespace utils {

    bool Files::isFile(const char *path) {
        struct stat buf{};
        stat(path, &buf);
        return S_ISREG(buf.st_mode);
    }

    bool Files::isDirectory(const char *path) {
        struct stat buf{};
        stat(path, &buf);
        return S_ISDIR(buf.st_mode);
    }

}