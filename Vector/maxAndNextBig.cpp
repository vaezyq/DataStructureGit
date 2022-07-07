//
// Created by 22126 on 2022/7/5.
//

#include <iostream>

int *maxAndNextMax(int *A, int lo, int hi) {
    if (lo + 2 >= hi) {
        auto *res = new int[2];
        if (A[lo] > A[lo + 1]) {
            res[0] = A[lo], res[1] = A[lo + 1];
        } else {
            res[0] = A[lo + 1], res[1] = A[lo];
        }
        return res;
    }
    auto mi = (lo + hi) >> 1;
    auto resA = maxAndNextMax(A, lo, mi);
    auto resB = maxAndNextMax(A, mi, hi);
    if (resA[0] >= resB[0]) {
        resA[1] = std::max(resA[1], resB[0]);
    } else {
        resA[1] = std::max(resA[0], resB[1]);
        resA[0] = resB[0];
    }
    return resA;
}

int main() {
    auto A = new int[]{1, 2, 3, 4, 5, 6, 7, 8};
    auto res = maxAndNextMax(A, 0, 8);
    std::cout << res[0] << " " << res[1];




}
