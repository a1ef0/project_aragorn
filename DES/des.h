#ifndef DES_H
#define DES_H

#include <cstdint>
#include <vector>

class des {
private:
    std::vector<uint8_t> master_key;
    std::vector<std::vector<uint8_t>> round_keys;
    std::vector<uint8_t> operate(int mode);
    std::vector<uint8_t> xor_arrays(const std::vector<uint8_t> & first,
                                    const std::vector<uint8_t> & second);

    std::vector<uint8_t> permute(const std::vector<uint8_t> & block,
                              const std::vector<uint8_t> & permutation_table);
public:
    des(const std::vector<uint8_t>& key);
    std::vector<uint8_t> encrypt(std::vector<uint8_t> message);
    std::vector<uint8_t> decrypt(std::vector<uint8_t> message);
};

#endif // DES_H
