#include <iostream>
#include <cstring>
#include "Bitmap.h"

using namespace std;

void Eratosthenes(int n, char *file) {
    Bitmap B(n);
    B.set(0);
    B.set(1);;
    for (auto i = 2; i < n; ++i) {
        if (!B.test(i)) {
            for (auto j = std::min(i, 46340) * std::min(i, 46340); j < n; j += i) {
                B.set(j);
            }
        }
    }
    B.dump(file);
}


int main() {

}
