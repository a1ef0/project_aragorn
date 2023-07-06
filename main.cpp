#include <iostream>
#include <algorithm>
#include <bitset>

#include <unordered_map>

#include "easy1.h"
#include "md5.h"
#include "des.h"

using namespace std;

int main() {
//    std::vector<uint8_t> key = {115, 101, 99, 114, 101, 116, 95, 107};
//    std::vector<uint8_t> pt = {72, 101, 108, 108, 111, 32, 119, 111};
//    std::vector<uint8_t> key = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
//    std::vector<uint8_t> pt = {1, 35, 69, 103, 137, 171, 205, 239};
//    uint64_t key = 0x133457799BBCDFF1;
//    uint64_t msg = 0x0123456789ABCDEF;
    uint64_t msg = 0x8787878787878787;
    uint64_t key = 0x0E329232EA6D0D73;
    des des(key);
    uint64_t ct = des.encrypt({msg})[0];
    uint64_t pt = des.decrypt({ct})[0];
    cout << ct << endl;
    cout << msg << ' ' << pt;
//    pprint("encrypted", ct);
//    pprint("decrypted", des.decrypt(ct));

    return 0;
}
