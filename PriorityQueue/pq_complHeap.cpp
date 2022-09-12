//
// Created by 王明龙 on 2022/9/9.
//


#include "pq_complHeap.h"

template<typename T>
void PQ_ComplHeap<T>::insert(T e) {
    this->insert(e);    //首先将新词条插入向量末尾
    percolateUp(this->_size - 1);     //对词条实施上滤操作
}

template<typename T>
T PQ_ComplHeap<T>::delMax() {
    auto maxElem = this->_elem[0];      //取出最大元素
    this->_elem[0] = this->_elem[--this->_size];   //将末尾元素移动到首元素位
    percolateDown(this->_elem, this->_size, 0);    //对新堆实施下滤
    return maxElem;
}



