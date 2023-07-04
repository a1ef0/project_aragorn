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

public:
    des(const uint64_t);
//    std::vector<uint64_t> encrypt(const std::vector<uint64_t> &);
//    std::vector<uint64_t> decrypt(const std::vector<uint64_t> &);
};

#endif // DES_H
