#include <iostream>
#include <algorithm>
#include <bitset>

#include <unordered_map>

#include "easy1.h"
#include "md5.h"
#include "des.h"

using namespace std;

void find_collisions() {
    md5 hash;

    unordered_map<int, pair<int, int>> map;

    int c = 0;
    for (int i = 0; i < 10'000'000; i++) {
        char buffer[33];
        uint32_t result = hash.digest(to_string(i));
        if (c < 10) {
            if (map[result].first != 0) {
                cout << "collision found!!" << endl;
                cout << map[result].second << ' ' << result << endl;
                c++;
            }
        } else {
            break;
        }
        map[result] = {map[result].first + 1, i};
    }
}

auto pprint = [](auto const remark, auto const& v)
{
    std::cout << remark << ": ";
    for (auto n : v)
        std::cout << int(n) << ' ';
    std::cout << '\n';
};

int main() {
//    std::vector<uint8_t> key = {115, 101, 99, 114, 101, 116, 95, 107};
//    std::vector<uint8_t> pt = {72, 101, 108, 108, 111, 32, 119, 111};
//    std::vector<uint8_t> key = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
//    std::vector<uint8_t> pt = {1, 35, 69, 103, 137, 171, 205, 239};
    uint64_t key = 0x133457799BBCDFF1;
    des des(key);
//    std::vector<uint8_t> ct = des.encrypt(pt);

//    pprint("encrypted", ct);
//    pprint("decrypted", des.decrypt(ct));

    return 0;
}
