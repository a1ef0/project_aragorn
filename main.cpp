#include <iostream>
#include <algorithm>
#include <bitset>

//#include "easy1.h"
#include "md5.h"

using namespace std;

void print_hash(uint8_t *p){
    for(unsigned int i = 0; i < 16; ++i){
        printf("%02x", p[i]);
    }
    printf("\n");
}

int main() {
//    Easy1 c(12123);
//    long pt = 12312331;
//    cout << pt << endl;
//    auto ct = c.encrypt(pt, 123);
//    cout << "----------------------------" << endl;
//    auto decrypted = c.decrypt(ct, 123);
//    cout << decrypted << endl;
    uint8_t result[16] = {};
    md5 hash;
    return 0;
}
