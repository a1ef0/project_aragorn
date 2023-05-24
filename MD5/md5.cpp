#include "md5.h"

#include <cstring>

MD5::MD5() {
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;

    count[0] = 0;
    count[1] = 0;

    std::memset(digest, 0, 16 * sizeof(UINT1));
    std::memset(buffer, 0, 64 * sizeof(UINT4));
}
