#include "des.h"

#include <algorithm>
//#define DEBUG

#ifdef DEBUG
#include <iostream>
using namespace std;

auto print = [](auto const remark, auto const& v)
{
    std::cout << remark << ": ";
    for (auto n : v)
        std::cout << int(n) << ' ';
    std::cout << '\n';
};
#endif

std::vector<uint8_t> PC_1 =
    {0x39, 0x31, 0x29, 0x21, 0x19, 0x11, 0x09,
     0x01, 0x3a, 0x32, 0x2a, 0x22, 0x1a, 0x12,
     0x0a, 0x02, 0x3b, 0x33, 0x2b, 0x23, 0x1b,
     0x13, 0x0b, 0x03, 0x3c, 0x34, 0x2c, 0x24,
     0x3f, 0x37, 0x2f, 0x27, 0x1f, 0x17, 0x0f,
     0x07, 0x3e, 0x36, 0x2e, 0x26, 0x1e, 0x16,
     0x0e, 0x06, 0x3d, 0x35, 0x2d, 0x25, 0x1d,
     0x15, 0x0d, 0x05, 0x1c, 0x14, 0x0c, 0x04};

std::vector<uint8_t> PC_2 =
    {0x0e, 0x11, 0x0b, 0x18, 0x01, 0x05, 0x03, 0x1c,
     0x0f, 0x06, 0x15, 0x0a, 0x17, 0x13, 0x0c, 0x04,
     0x1a, 0x08, 0x10, 0x07, 0x1b, 0x14, 0x0d, 0x02,
     0x29, 0x34, 0x1f, 0x25, 0x2f, 0x37, 0x1e, 0x28,
     0x33, 0x2d, 0x21, 0x30, 0x2c, 0x31, 0x27, 0x38,
     0x22, 0x35, 0x2e, 0x2a, 0x32, 0x24, 0x1d, 0x20};

std::vector<uint8_t> SHIFT =
    {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

std::vector<uint8_t> des::permute(const std::vector<uint8_t> & block,
                          const std::vector<uint8_t> & permutation_table) {
    std::vector<uint8_t> result(permutation_table.size() / 8);
    for (size_t i = 0; i < permutation_table.size(); i++) {
        // the bit idx we want to set 1
        size_t idx = permutation_table[i] - 1;
        result[i / 8] <<= 1;
        if (block[idx / 8] & (1 << (8 - permutation_table[i] % 8))){
            result[i / 8] = result[i / 8] | 1;
        }
    }

    return result;
}

std::pair<std::vector<uint8_t>, std::vector<uint8_t>>
half_split(const std::vector<uint8_t>& input) {
    size_t result_len = input.size() / 2 + input.size() % 2;
    std::pair<std::vector<uint8_t>, std::vector<uint8_t>> result;
    result.first = std::vector<uint8_t>(result_len);
    result.second = std::vector<uint8_t>(result_len - input.size() % 2);
    std::copy(input.begin(), input.begin() + result_len, result.first.begin());
    std::copy(input.begin() + result_len, input.end(), result.second.begin());

    return result;
}

std::vector<uint8_t> concat(const std::vector<uint8_t>& left,
                            const std::vector<uint8_t>& right) {
    std::vector<uint8_t> result;
    result.reserve(left.size() + right.size());
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());

    return result;
}

des::des(const std::vector<uint8_t>& key) {
    master_key = key;

    std::vector<uint8_t> cur = permute(key, PC_1);

    std::vector<uint8_t> left, right;
    auto tmp = half_split(cur);
    left = tmp.first;
    right = tmp.second;

    round_keys = std::vector<std::vector<uint8_t>>(16, std::vector<uint8_t>());
    for (int i = 0; i < 16; ++i) {
        std::rotate(left.begin(), left.begin() + SHIFT[i], left.end());
        std::rotate(right.begin(), right.begin() + SHIFT[i], right.end());

    #ifdef DEBUG
        print("left", left);
        print("right", right);
    #endif
        auto tmp = concat(left, right);
        round_keys[i] = permute(tmp, PC_2);
    }

}
