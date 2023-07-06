#ifndef DES_H
#define DES_H

#include <cstdint>
#include <vector>

class des {

private:
    uint64_t master_key;
    std::vector<uint64_t> round_keys = std::vector<uint64_t>(16);

    template <typename T>
    requires (std::is_integral<T>::value)
    T permute(const T &, uint8_t, const std::vector<uint8_t> &);

    std::vector<uint64_t> operate(uint8_t mode, uint64_t);
    uint64_t feistel(uint64_t, uint64_t);
    void set_subkeys();

public:
    des(const uint64_t);
    des(const std::vector<uint8_t> &);
    std::vector<uint64_t> encrypt(const std::vector<uint64_t> &);
    std::vector<uint64_t> decrypt(const std::vector<uint64_t> &);
};

#endif // DES_H
