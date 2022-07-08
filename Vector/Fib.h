//
// Created by 22126 on 2022/5/28.
//

#ifndef DATASTRUCTUREGIT_FIB_H
#define DATASTRUCTUREGIT_FIB_H


class Fib {
private:
    long f;
    long g; //f = fib(k - 1), g = fib(k)
public:
    Fib(int n);

    int get();
    int next();
    int prev();

};


#endif //DATASTRUCTUREGIT_FIB_H
