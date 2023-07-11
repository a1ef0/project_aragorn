#ifndef DES_H
#define DES_H

#include <cstdint>
#include <vector>

class des {

private:
    uint64_t master_key;
    std::vector<uint64_t> round_keys = std::vector<uint64_t>(16);

    /**
     * Do a permutation of a block with the given size and SBOX
     * @tparam T type of values in the block
     * @param block to permute
     * @param bit_count of the block
     * @param sbox to use in permutation
     * @return permuted block of data
     */
    template <typename T>
    requires (std::is_integral<T>::value)
    T permute(const T &, uint8_t, const std::vector<uint8_t> &);

    /**
     * Operate on the bytes of data. 2 possible modes of operation:
     * 0 - encryption, 1 - decryption
     * @param mode 0 for encryption, 1 for decryption
     * @param message to process
     * @return encrypted or decrypted message
     */
    std::vector<uint8_t> operate(uint8_t, std::vector<uint8_t>);

    /**
     * DES Feistel function
     * @param block of data to process
     * @param key round key to use
     * @return result of Feistel function
     */
    uint64_t feistel(uint64_t, uint64_t);

    /**
     * Preprocess message, i.e. add padding and convert to feasible blocks of
     * data
     * @return array with blocks of data
     */
    std::vector<uint64_t>
    preprocess_message(std::vector<uint8_t>);

    /**
     * Postprocess message, i.e. remove padding and convert message to bytes
     * @return bytes
     */
    std::vector<uint8_t>
    postprocess_message(const std::vector<uint64_t>&);

    /**
     * Generate the subkeys from the DES key schedule
     */
    void set_subkeys();

    /**
     * Pad the message according to the PKCS7 padding scheme
     * @param message to pad
     * @return padded message
     */
    std::vector<uint8_t> pad(std::vector<uint8_t>);

    /**
     * Unpad the message according to the PKCS7 padding scheme
     * @param message to unpad
     * @return unpadded message
     */
    std::vector<uint8_t> unpad(std::vector<uint8_t>);

public:
    des(const uint64_t);
    des(const std::vector<uint8_t> &);

    /**
     * Encrypt the given block of data within the given context
     * @param message to encrypt
     * @return encrypted data
     */
    std::vector<uint8_t> encrypt(const std::vector<uint8_t> &);

    /**
     * Decrypt the given block of data within the given context
     * @param message to decrypt
     * @return decrypted data
     */
    std::vector<uint8_t> decrypt(const std::vector<uint8_t> &);
};

#endif // DES_H
