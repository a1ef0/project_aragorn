#ifndef EASY1_CPP
#define EASY1_CPP

#include "easy1.h"
#include <cassert>
#include <algorithm>

#include <iostream>
#include <bitset>

using namespace std;

void print_demuxed(std::vector<uint8_t>& demuxed) {
    for_each(demuxed.begin(), demuxed.end(), [](uint8_t n) {
        std::bitset<6> a(n);
        std::cout << a << '\t';
    });
    std::cout << std::endl;
}

Easy1::Easy1(size_t rounds) {
    this->rounds = rounds;
}

uint8_t Easy1::sbox(uint8_t x, bool inv) {
    std::vector<uint8_t> box;
    if (inv) {
        box = SBOX_INV;
    } else {
        box = SBOX;
    }
    assert(0 <= x && x < 64);
    return box[x];
}

size_t Easy1::pbox(size_t x, bool inv) {
    std::vector<uint8_t> box;
    if (inv) {
        std::vector<uint8_t> pbox_inv(PBOX_SIZE);
        for (size_t i = 0; i < PBOX_SIZE; i++)
            pbox_inv[PBOX[i]] = i;
        box = pbox_inv;
    } else {
        box = PBOX;
    }

    size_t y = 0;

    for (size_t i = 0; i < PBOX_SIZE; i++) {
        if ((x & (size_t(1) << i)) != 0) {
            y = y ^ (size_t(1) << box[i]);
        }
    }

    return y;
}


std::vector<uint8_t> Easy1::demux(size_t x) {
    std::vector<uint8_t> y;
    for (size_t i = 0; i < SUBKEY_SIZE; i++) {
        y.push_back((x >> (i * SUBKEY_SIZE)) & 0x3f);
    }
    std::reverse(y.begin(), y.end());
    return y;
}


size_t Easy1::mux(const std::vector<uint8_t>& x) {
    size_t y = 0;
    for (size_t i = 0; i < SUBKEY_SIZE; i++) {
        y = (y << SUBKEY_SIZE) ^ (x[i] & 0x3f);
    }

    return y;
}

std::vector<uint8_t> Easy1::mix(const size_t& key) {
    auto demuxed_key = demux(key);
    std::vector<uint8_t> result;
    for (size_t i = 0; i < SUBKEY_SIZE; ++i) {
        result.push_back(state[i] ^ demuxed_key[i]);
    }
    return result;
}

size_t Easy1::round(const size_t& key) {
    for (auto& e : state) {
        e = sbox(e, false);
    }

    state = demux(pbox(mux(state), false));

    state = mix(key);

    return mux(state);
}

size_t Easy1::unround(const size_t& key) {
    state = mix(key);

    state = demux(pbox(mux(state), true));

    for (auto& e : state) {
        e = sbox(e, true);
    }

    return mux(state);
}

size_t Easy1::encrypt(const size_t& pt, const size_t& key) {
    state = demux(pt);

    size_t result = 0l;
    for (size_t i = 0; i < rounds; i++) {
        result = round(key);
    }

    return result;
}

size_t Easy1::decrypt(const size_t& ct, const size_t& key) {
    state = demux(ct);

    size_t result = 0l;
    for (size_t i = 0; i < rounds; i++) {
        result = unround(key);
    }

    return result;
}

#endif // EASY1_CPP
