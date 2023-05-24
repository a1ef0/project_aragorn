/*
 * Derived from the RSA Data Security, Inc. MD5 Message-Digest Algorithm.
 * RFC 1321 ( https://www.rfc-editor.org/rfc/rfc1321 )
*/

#ifndef MD5_H
#define MD5_H

#include <bits/types/FILE.h>
#include <cstddef>
#include <cstdint>
#include <string>

typedef uint32_t UINT4;
typedef uint16_t UINT2;
typedef uint8_t  UINT1;

class MD5 {
private:
    UINT4 buffer[64]; // bytes that didn't fit in last 64 byte chunk
    UINT4 count[2];   // 64bit counter for number of bits (lo, hi)
    UINT4 state[4];   // digest so far
    UINT1 digest[16]; // the result

    static UINT1 PADDING[64];
    static UINT4 K[64];

    static UINT4 S1[4];
    static UINT4 S2[4];
    static UINT4 S3[4];
    static UINT4 S4[4];

    /* F, G, H and I are basic MD5 functions.
     */
    UINT4 F(UINT4 x, UINT4 y, UINT4 z);
    UINT4 G(UINT4 x, UINT4 y, UINT4 z);
    UINT4 H(UINT4 x, UINT4 y, UINT4 z);
    UINT4 I(UINT4 x, UINT4 y, UINT4 z);

    UINT4 rotate_left(UINT4 x, UINT4 n);

    /* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
     * Rotation is separate from addition to prevent recomputation.
     */
    void FF(UINT4& a, UINT4 b, UINT4 c, UINT4 d, UINT4 x, UINT4 s, UINT4 ac);
    void GG(UINT4& a, UINT4 b, UINT4 c, UINT4 d, UINT4 x, UINT4 s, UINT4 ac);
    void HH(UINT4& a, UINT4 b, UINT4 c, UINT4 d, UINT4 x, UINT4 s, UINT4 ac);
    void II(UINT4& a, UINT4 b, UINT4 c, UINT4 d, UINT4 x, UINT4 s, UINT4 ac);

public:
    MD5(void);
    void update(uint8_t *input, size_t input_len);
    void finalize(void);
    void step(UINT4 *buffer, UINT4 *input);
    std::string hexdigest(char *input);
};

#endif // MD5_H
