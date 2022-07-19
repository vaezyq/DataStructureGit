#include <iostream>
#include <cstring>
#include "Bitmap.h"

using namespace std;

void Eratosthenes(int n, char *file) {
    Bitmap B(n);

    B.set(0);
    B.set(1);;
    B.bits2string(100);
    for (auto i = 2; i < n; ++i) {
        if (!B.test(i)) {
            for (auto j = std::min(i, 46340) * std::min(i, 46340); j < n; j += i) {
                B.set(j);
            }
        }
    }
    B.dump(file);
}


void printSmallRangeData(int n, int *A, int m) {
    Bitmap B(m);
    for (auto i = 0; i < n; ++i) {
        B.set(A[i]);
    }
    B.bits2string(m);
}

int main() {

    char *file = "primer.txt";
    auto n{100};
    Eratosthenes(n, file);
    Bitmap B2(file, 100);
    cout << B2.bits2string(100);


}
