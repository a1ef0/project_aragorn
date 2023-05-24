#ifndef EASY1_H
#define EASY1_H

#include <vector>

class Easy1 {
private:
    const std::vector<long> SBOX =
                   {16, 42, 28,  3, 26,  0, 31, 46,
                    27, 14, 49, 62, 37, 56, 23,  6,
                    40, 48, 53,  8, 20, 25, 33,  1,
                    2,  63, 15, 34, 55, 21, 39, 57,
                    54, 45, 47, 13,  7, 44, 61,  9,
                    60, 32, 22, 29, 52, 19, 12, 50,
                    5,  51, 11, 18, 59, 41, 36, 30,
                    17, 38, 10,  4, 58, 43, 35, 24};

    const std::vector<long> SBOX_INV =
                   { 5, 23, 24,  3, 59, 48, 15, 36,
                    19, 39, 58, 50, 46, 35,  9, 26,
                     0, 56, 51, 45, 20, 29, 42, 14,
                    63, 21,  4,  8,  2, 43, 55,  6,
                    41, 22, 27, 62, 54, 12, 57, 30,
                    16, 53,  1, 61, 37, 33,  7, 34,
                    17, 10, 47, 49, 44, 18, 32, 28,
                    13, 31, 60, 52, 40, 38, 11, 25};

    const std::vector<long> PBOX =
                   {24,  5, 15, 23, 14, 32,
                    19, 18, 26, 17,  6, 12,
                    34,  9,  8, 20, 28,  0,
                     2, 21, 29, 11, 33, 22,
                    30, 31,  1, 25,  3, 35,
                    16, 13, 27,  7, 10,  4};

    const long SUBKEY_SIZE = 6;
    const long PBOX_SIZE = 36;
    const long SBOX_SIZE = 64;
    std::vector<long> state;
    long rounds;

public:
    Easy1(long rounds);

    long sbox(long, bool);
    long pbox(long, bool);

    /**
    * @brief demux the 36-bit to 6 6-bit values, words are little-endian
    * @param x - 36 bit value to demux
    * @return 6 6-bit values, results of demux operation
    */
    std::vector<long> demux(long x);

    /**
    * @brief mux the 6 6-bit values into 36-bit bit one
    * @param x - vector of 6 6-bit values to mux
    * @return 36-bit result of mux
    */
    long mux(const std::vector<long>& x);

    /**
     * @brief mix the given
     * @param k - the key to mix the current state with
     * @return xored result
     */
    std::vector<long> mix(const long& key);

    /**
     * @brief perform 1 round of encryption
     * @param key - round key to be added
     * @return encrypted state
     */
    long round(const long& key);

    /**
     * @brief undo 1 round of encryption
     * @param key - round key to be added
     * @return decrypted state
     */
    long unround(const long& key);

    /**
     * @brief encrypt given plaintext with a key
     * @param pt - plaintext to encrypt
     * @param key - key to encrypt with
     * @return ct - ciphertext
     */
    long encrypt(const long& pt, const long& key);

    /**
     * @brief encrypt given plaintext with a key
     * @param ct - ciphertext to decrypt
     * @param key - key to decrypt with
     * @return pt - plaintext
     */
    long decrypt(const long& ct, const long& key);

};

#endif // EASY1_H
