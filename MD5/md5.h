#ifndef MD5_H
#define MD5_H

/* MD5.H - header file for MD5C.C
 */

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.
These notices must be retained in any copies of any part of this
documentation and/or software.
 */
#include <inttypes.h>
#include <string>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <iostream>

/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* UINT2 defines a two byte word */
typedef uint16_t  UINT2;

/* UINT4 defines a four byte word */
typedef uint32_t UINT4;


class md5 {
private:

    UINT4 state[4];                                   /* state (ABCD) */
    UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64];                         /* input buffer */
    void reset();
    void update(unsigned char *, unsigned int);
    void final(unsigned char [16]);

public:
    md5();
    uint32_t digest(const std::string& string);

};

//void find_collisions() {
//
//    using namespace std;
//
//    md5 hash;
//
//    unordered_map<int, pair<int, int>> map;
//
//    int c = 0;
//    for (int i = 0; i < 10'000'000; i++) {
//        char buffer[33];
//        uint32_t result = hash.digest(to_string(i));
//        if (c < 10) {
//            if (map[result].first != 0) {
//                cout << "collision found!!" << endl;
//                cout << map[result].second << ' ' << result << endl;
//                c++;
//            }
//        } else {
//            break;
//        }
//        map[result] = {map[result].first + 1, i};
//    }
//}

#endif // MD5_H
