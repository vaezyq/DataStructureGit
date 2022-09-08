//
// Created by 22126 on 2022/8/21.
//

#ifndef DATASTRUCTUREGIT_AVL_H
#define DATASTRUCTUREGIT_AVL_H

#include "BST.h"

template<typename T>
class AVL : public BST<T> {    //基于BST派生AVL树
public:
    BinNodePos insert(T const &e);   //插入(重写)
    bool remove(const T &e);       //删除(重写)


#define Balanced(x) (stature((x).lChild) == stature((x).rChild))  //理想平衡
#define BalFac(x) (stature((x).lChild) - stature((x).rChild)) //平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2)) //AVL平衡条件
};




#endif //DATASTRUCTUREGIT_AVL_H













