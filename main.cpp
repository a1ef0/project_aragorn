#include <iostream>
#include <algorithm>
#include <bitset>

#include "easy1.h"

using namespace std;


int main()
{
    Easy1 c(1);
    long pt = 12312331;
    auto ct = c.encrypt(pt, 123);
    cout << pt << endl;
    cout << "----------------------------" << endl;
    auto decrypted = c.decrypt(ct, 123);
    cout << decrypted << endl;
    return 0;
}
