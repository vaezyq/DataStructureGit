//
// Created by 王明龙 on 2022/9/9.
//

#ifndef DATASTRUCTUREGIT_PQ_COMPLHEAP_H
#define DATASTRUCTUREGIT_PQ_COMPLHEAP_H

#include "../Vector/Vector.h"
#include "pq.h"


template<typename T>

struct PQ_ComplHeap : public Vector<T>, public PQ<T> {
    PQ_ComplHeap() {};    //默认构造函数

    PQ_ComplHeap(T *A, int n) {
        this->copyFrom(A, 0, n);
        heapify(A, n);      //基于floyd的构造
    }

    void insert(T);  //按照比较器确定的优先级次序，插入词条
    T getMax() { return this->_elem[0]; };   //获取优先级最高的元素
    T delMax();  //删除优先级最高的元素
};




#endif //DATASTRUCTUREGIT_PQ_COMPLHEAP_H













