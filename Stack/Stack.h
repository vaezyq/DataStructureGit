//
// Created by 22126 on 2022/6/18.
//

#ifndef DATASTRUCTUREGIT_STACK_H
#define DATASTRUCTUREGIT_STACK_H

#include "../Vector/Vector.h"


template<typename T>

class Stack : public Vector<T> {
public:     //size(),empty()接口均可直接使用
    void push(T const &e);  //入栈：新元素作为向量尾元素插入

    T pop() ;

    T &top() ;
};


template
class Stack<char>;


#endif //DATASTRUCTUREGIT_STACK_H
