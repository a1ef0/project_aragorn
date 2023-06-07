#include "des.h"

#include <algorithm>
#define DEBUG

#ifdef DEBUG
#include <iostream>

namespace std {

template <typename T>
vector<T> operator +(const vector<T>& left, const vector<T>& right) {
    vector<T> result;
    result.reserve(left.size() + right.size());
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());

    return result;
}

}

auto print = [](auto const remark, auto const& v) {
    using namespace std;
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

std::vector<uint8_t> IP =
    {0x3a, 0x32, 0x2a, 0x22, 0x1a, 0x12, 0x0a, 0x02,
     0x3c, 0x34, 0x2c, 0x24, 0x1c, 0x14, 0x0c, 0x04,
     0x3e, 0x36, 0x2e, 0x26, 0x1e, 0x16, 0x0e, 0x06,
     0x40, 0x38, 0x30, 0x28, 0x20, 0x18, 0x10, 0x08,
     0x39, 0x31, 0x29, 0x21, 0x19, 0x11, 0x09, 0x01,
     0x3b, 0x33, 0x2b, 0x23, 0x1b, 0x13, 0x0b, 0x03,
     0x3d, 0x35, 0x2d, 0x25, 0x1d, 0x15, 0x0d, 0x05,
     0x3f, 0x37, 0x2f, 0x27, 0x1f, 0x17, 0x0f, 0x07};

std::vector<uint8_t> E =
    {0x20, 0x01, 0x02, 0x03, 0x04, 0x05,
     0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
     0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11,
     0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
     0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
     0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
     0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x01};

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

des::des(const std::vector<uint8_t>& key) {
    if (key.size() < 8) {
        throw std::runtime_error("key must be at least 8 bytes long");
    } else {
        std::copy(key.begin(), key.begin() + 8, master_key.begin());
    }

    std::vector<uint8_t> cur = permute(key, PC_1);

    std::vector<uint8_t> left, right;
    auto tmp = half_split(cur);
    left = tmp.first;
    right = tmp.second;

    this->round_keys = std::vector<std::vector<uint8_t>>(16, std::vector<uint8_t>());
    for (int i = 0; i < 16; ++i) {
        std::rotate(left.begin(), left.begin() + SHIFT[i], left.end());
        std::rotate(right.begin(), right.begin() + SHIFT[i], right.end());

    #ifdef DEBUG
        print("left", left);
        print("right", right);
    #endif
        auto tmp = left + right;
        this->round_keys[i] = permute(tmp, PC_2);
    }
}

std::vector<uint8_t> des::pad(std::vector<uint8_t> msg) {
    uint8_t padding_value = 8 - msg.size() % 8;
    for (uint8_t i = 0; i < padding_value; i++) {
        msg.push_back(padding_value);
    }
    return msg;
}

std::vector<uint8_t> des::unpad(std::vector<uint8_t> msg) {
    uint8_t padding_value = msg[msg.size() - 1];
    for (uint8_t i = 0; i < padding_value; i++) {
        msg.pop_back();
    }
    return msg;
}

std::vector<std::vector<uint8_t>> des::split_msg(const std::vector<uint8_t> & msg) {
    std::vector<std::vector<uint8_t>> result(msg.size() / 8, std::vector<uint8_t>());
    for (size_t i = 0; i < msg.size(); i++) {
        result[i / 8].push_back(msg[i]);
    }
    return result;
}

std::vector<uint8_t> des::concat_blocks(const std::vector<std::vector<uint8_t>> & blocks) {
    std::vector<uint8_t> result(blocks.size() * 8);
    for (size_t i = 0; i < result.size(); i++) {
        result[i] = blocks[i / 8][i % 8];
    }
    return result;
}

std::vector<uint8_t> des::operate(int mode, std::vector<uint8_t> message) {
    // 0 - encrypt
    // 1 - decrypt
    if (mode == 0) {
        message = pad(message);
    } else if (mode == 1){
        if (message.size() % 8 != 0) {
            throw std::runtime_error("message length must be a multiple of 8 to"
                                     "be decrypted");
        }
    } else {
        return message;
    }
    std::vector<std::vector<uint8_t>> blocks = split_msg(message);
    std::vector<std::vector<uint8_t>> result(blocks.size());
    for (auto& block : blocks) {
        block = permute(block, IP);

        auto tmp = half_split(block);
        std::vector<uint8_t> left, right;
        left = tmp.first;
        right = tmp.second;
        // 16 rounds of encryption
        //for (uint8_t i = 0; i < 16; i++) {

        //}
    }
    return {};
}