//
// Created by 22126 on 2022/5/30.
//

#include "Bitmap.h"
#include <cstring>
#include <cstdio>
#include <set>

using namespace std;


void Bitmap::init(int n) {

    M = new unsigned char[N = (n + 7) / 8];
    memset(M, 0, N);
}

Bitmap::Bitmap(char *file, int n) {
    init(n);
    FILE *fp = fopen(file, "r");
    fread(M, sizeof(unsigned char), N, fp);
    fclose(fp);
}

void Bitmap::set(int k) {
    expand(k);
    M[k >> 3] |= (0x80 >> (k & 0x07));
}

void Bitmap::clear(int k) {
    M[k >> 3] &= ~(0x80 >> (k & 0x07));
}

bool Bitmap::test(int k) {
    return M[k >> 3] & (0x80 >> (k & 0x07));
}

void Bitmap::dump(char *file) {
    FILE *fp = fopen(file, "w");
    fwrite(M, sizeof(unsigned char), N, fp);
    fclose(fp);
}

void Bitmap::expand(int k) {
    if (k < 8 * N) return;
    int oldN = N;
    auto oldM = M;
    init(2 * k);
    memcpy_s(M, N, oldM, oldN);
    delete[]oldM;
}

char *Bitmap::bits2string(int n) {
    expand(n - 1);
    auto s = new char[n + 1];
    s[n] = '\0';
    for (auto i = 0; i < n; ++i) {
        s[i] = test(i) ? '1' : '0';
    }
    return s;
}











//
//void Bitmap::init(int n) {
//
//    M = new unsigned char[N = (n + 7) / 8];
//    memset(M, 0, N);
//
//}
//
//
//
//void Bitmap::set(int k) {
//    expand(k);
//    M[k >> 3] |= (0x80 >> (k & 0x07));
//}
//
//void Bitmap::clear(int k) {
//
//
//    expand(k);
//    M[k >> 3] &= ~(0x80 >> (k & 0x07));
//}
//
//bool Bitmap::test(int k) {
//    return M[k >> 3] & (0x80 >> (k & 0x07));
//}
//
//void Bitmap::dump(char *file) {
//    FILE *fp = fopen(file, "w");
//    fwrite(M, sizeof(unsigned char), N, fp);
//    fclose(fp);
//}
//
//void Bitmap::expand(int k) {
//    if (k < 8 * N) return;
//    int oldN = N;
//    unsigned char *oldM = M;
//    init(2 * k);
//    memcpy(M, oldM, N);
//    delete[] oldM;
//}
//
//
//Bitmap::Bitmap(char *file, int n) {
//
//    init(n);
//    FILE *fp = fopen(file, "r");
//    fread(M, sizeof(unsigned char), N, fp);
//    fclose(fp);
//
//}
//
//char *Bitmap::bits2string(int n) {
//    expand(n - 1);
//    char *s = new char[n + 1];
//    s[n] = '\0';
//    for (auto i = 0; i < n; i++) {
//        s[i] = test(i) ? '1' : '0';
//    }
//    return s;
//}
//
//
//








