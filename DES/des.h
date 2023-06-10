#ifndef DES_H
#define DES_H

#include <cstdint>
#include <vector>

class des {
private:
    std::vector<uint8_t> master_key;
    std::vector<std::vector<uint8_t>> round_keys;

private:
    std::vector<uint8_t> operate(int, std::vector<uint8_t>);
    std::vector<uint8_t> xor_arrays(const std::vector<uint8_t> & ,
                                    const std::vector<uint8_t> & );

    std::vector<uint8_t> permute(const std::vector<uint8_t> &,
                              const std::vector<uint8_t> &,
                              int);

    std::vector<uint8_t> pad(std::vector<uint8_t>);
    std::vector<uint8_t> unpad(std::vector<uint8_t>);

    std::vector<std::vector<uint8_t>> split_msg(const std::vector<uint8_t> &);
    std::vector<uint8_t> concat_blocks(const std::vector<std::vector<uint8_t>> &);

    std::vector<uint8_t> sbox(const std::vector<uint8_t> & block);

public:
    des(const std::vector<uint8_t> &);
    std::vector<uint8_t> encrypt(const std::vector<uint8_t> &);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t> &);
};

#endif // DES_H
