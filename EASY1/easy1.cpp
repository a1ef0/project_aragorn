#ifndef EASY1_CPP
#define EASY1_CPP

#include "easy1.h"
#include <cassert>
#include <algorithm>

#include <iostream>
#include <bitset>

void print_demuxed(std::vector<long> demuxed) {
    for_each(demuxed.begin(), demuxed.end(), [](int n){
        std::bitset<6> a(n);
        std::cout << a << '\t';
    });
    std::cout << std::endl;
}

Easy1::Easy1(long rounds) {
    this->rounds = rounds;
}

long Easy1::sbox(long x, bool inv) {
    std::vector<long> box;
    if (inv) {
        box = SBOX_INV;
    } else {
        box = SBOX;
    }
    assert(0 <= x && x < 64);
    return box[x];
}

long Easy1::pbox(long x, bool inv) {
    std::vector<long> box;

    if (inv) {
        std::vector<long> pbox_inv(PBOX_SIZE);
        for (int i = 0; i < PBOX_SIZE; i++)
            pbox_inv[PBOX[i]] = i;
        box = pbox_inv;
    } else {
        box = PBOX;
    }

    long y = 0l;

    for (std::size_t i = 0; i < PBOX_SIZE; i++) {
        if ((x & (1l << i)) != 0) {
            y = y ^ (1l << box[i]);
        }
    }

    return y;
}


std::vector<long> Easy1::demux(long x) {
    std::vector<long> y;
    for (std::size_t i = 0; i < SUBKEY_SIZE; i++) {
        y.push_back((x >> (i * SUBKEY_SIZE)) & 0x3f);
    }
    std::reverse(y.begin(), y.end());
    return y;
}


long Easy1::mux(const std::vector<long>& x) {
    long y = 0;
    for (long i = 0; i < SUBKEY_SIZE; i++) {
        y = (y << SUBKEY_SIZE) ^ (x[i] & 0x3f);
    }

    return y;
}

std::vector<long> Easy1::mix(const long & key) {
    auto demuxed_key = demux(key);
    std::vector<long> result;
    for (std::size_t i = 0; i < SUBKEY_SIZE; ++i) {
        result.push_back(state[i] ^ demuxed_key[i]);
    }
    return result;
}

long Easy1::round(const long & key) {
    for (auto& e : state) {
        e = sbox(e, false);
    }

    state = demux(pbox(mux(state), false));

    state = mix(key);

    return mux(state);
}

long Easy1::unround(const long& key) {
    state = mix(key);

    state = demux(pbox(mux(state), true));

    for (auto& e : state) {
        e = sbox(e, true);
    }

    return mux(state);
}

long Easy1::encrypt(const long& pt, const long& key) {
    state = demux(pt);

    long result = 0l;
    for (std::size_t i = 0; i < rounds; i++) {
        result = round(key);
    }

    return result;
}

long Easy1::decrypt(const long& ct, const long& key) {
    state = demux(ct);

    long result = 0l;
    for (std::size_t i = 0; i < rounds; i++) {
        result = unround(key);
    }

    return result;
}

#endif // EASY1_CPP
