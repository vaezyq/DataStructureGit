//
// Created by 22126 on 2022/6/18.
//

#ifndef DATASTRUCTUREGIT_STACK_H
#define DATASTRUCTUREGIT_STACK_H
#include "../Vector/Vector.h"


template <typename T>

class Stack :public Vector<T>{
public:
    void push(T const &e);
    T pop();
    T &top();


};




#endif //DATASTRUCTUREGIT_STACK_H
