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

int main() {
    std::vector<uint8_t> key = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
    des des(key);
    return 0;
}
