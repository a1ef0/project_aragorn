#include <iostream>
#include <algorithm>
#include <bitset>

#include <unordered_map>

//#include "easy1.h"
#include "md5.h"

using namespace std;

void print_hash(uint8_t *p){
    for(unsigned int i = 0; i < 16; ++i){
        printf("%02x", p[i]);
    }
    printf("\n");
}

int main() {
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

    return 0;
}
