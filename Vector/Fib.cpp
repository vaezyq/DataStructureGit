//
// Created by 22126 on 2022/5/28.
//

#include "Fib.h"


Fib::Fib(int n) {
    f = 0;
    g = 1;
}

int Fib::get() {
    return g;
}

int Fib::next() {
    g = g + f;
    f = g - f;
    return g;
}

int Fib::prev() {
    f = g - f;
    g = g - f;
    return g;
}
















//Fib::Fib(int n) {
//    f = 1;
//    g = 0;
//    while (g < n) { next(); };
//}
//
//int Fib::get() {
//    return g;
//}
//
//int Fib::next() {
//    g = +f;
//    f = g - f;
//    return g;
//}
//
//int Fib::prev() {
//    f = g - f;
//    g -= f;
//    return g;
//}
