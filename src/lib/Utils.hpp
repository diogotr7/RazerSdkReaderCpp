#ifndef UTILS
#define UTILS
#include <algorithm>
#include <cstdint>

inline size_t ToReadIndex(const uint32_t writeIndex) {
    if (writeIndex == 0) {
        return 9;
    }
    return writeIndex - 1;
}

#endif
