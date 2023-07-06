#include <iostream>
#include <algorithm>
#include <bitset>

#include <unordered_map>

#include "easy1.h"
#include "md5.h"
#include "des.h"

using namespace std;

int main() {
    auto print = [](auto const remark, auto const& v) {
        using namespace std;
        std::cout << remark << ": ";
        for (auto n : v)
            std::cout << int(n) << ' ';
        std::cout << '\n';
    };
    std::vector<uint8_t> key = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
    std::vector<uint8_t> pt = {1, 35, 69, 103, 137, 171, 205, 239};
    des des(key);
    auto ct = des.encrypt(pt);
    auto pt_ = des.decrypt(ct);
    print("pt", pt);
    print("ct", ct);
    print("decrypted", pt_);
    return 0;
}
