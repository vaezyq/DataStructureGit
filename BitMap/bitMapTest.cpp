#include <iostream>
#include <cstring>
#include "Bitmap.h"

using namespace std;

int dice(int n) {
    return rand() % n;
}


int testBitMap(int n) {
    bool *B = new bool[n];
    memset(B, 0, n * sizeof(bool));
    Bitmap M(n);

    for (int i = 0; i < 9 * n; ++i) {
        int k = dice(n);
        cout << "set(" << k << ")..." << endl;
        B[k] = true;
        M.set(k);
        printf("done\n CRC: ");
        for (int j = 0; j < n; j++)
            printf("%6c", B[j] == M.test(j) ? ' ' : '!');
        printf("\n B[]: ");
        for (int j = 0; j < n; j++)
            printf("%6c", B[j] ? 'x' : '.');
        printf("\n M[]: ");
        for (int j = 0; j < n; j++)
            printf("%6c", M.test(j) ? 'x' : '.');
        printf("\n\n\n");
    }
    delete[]B;
    return 0;
}


int main() {
    srand((unsigned int) time(NULL));
    return testBitMap(10);
}
