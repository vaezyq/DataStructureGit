//
// Created by 22126 on 2022/7/4.
//

//习题1-29
#include <iostream>

using namespace std;

int hailstone(int &e) {
    int step = 0;
    while (1 != e) {
        e % 2 ? e = 3 * e + 1 : e = e >> 1;
        step++;
    }
    return ++step;
}

int main() {
    int a = 7;
    cout << hailstone(a);
}