//
// Created by 22126 on 2022/7/10.
//
#include "Stack.h"

// 进制转换:递归实现
void convert_R(Stack<char> &S, long long n, int base) {
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    if (0 >= n) return;

    convert_R(S, n / base, base);
    S.push(digit[static_cast<int>(n % base)]);
}


// 进制转换:迭代实现
void convert_I(Stack<char> &S, long long n, int base) {
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    while (0 < n) {
        S.push(digit[static_cast<int>(n % base)]);
        n /= base;
    }
}
