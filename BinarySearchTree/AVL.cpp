//
// Created by 22126 on 2022/8/21.
//

#include "AVL.h"

template<typename T>
BinNode<T> *AVL<T>::insert(const T &e) {
    BinNodePos&x = this->search(e);
    if (x) return x;   //如果已经存在，则直接返回
    BinNodePos xx = x = new BinNode<T>(e, this->_hot); //创建新节点，key为e,父节点为_hot
    this->_size++;     //更新全树规模
    for (auto g = this->_hot; g; g = g->parent) {    //从_hot起逐层检查各代祖先g


    }
    return xx;  //返回新节点位置


}