#ifndef UTILS
#define UTILS
#include <algorithm>
#include <cstdint>

inline int32_t ToReadIndex(const uint32_t writeIndex) {
    return static_cast<int32_t>(std::max(9u, writeIndex - 1));
}

#endif
