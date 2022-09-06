//
// Created by 22126 on 2022/8/20.
//

#ifndef DATASTRUCTUREGIT_BST_H
#define DATASTRUCTUREGIT_BST_H

#include "../Tree//BinTree.h"

template<typename T>
class BST : public BinTree<T> {     //由二叉树BinTree派生

public:   //以virtual修饰，以便派生类的重写

    virtual BinNodePos&search(const T &e);    //查找

    virtual BinNodePos&searchIn(BinNodePos&v, const T &e, BinNodePos&hot);    //查找,递归版本

    virtual BinNodePos insert(const T &e);    //插入

    virtual bool remove(const T &e);   //删除

    virtual BinNodePos removeAt(BinNodePos&x, BinNodePos&hot);


protected:

    BinNodePos _hot;   //命中节点的父亲

    BinNodePos connect34(BinNodePos, BinNodePos, BinNodePos,
                         BinNodePos, BinNodePos, BinNodePos, BinNodePos);  //3+4重构
    BinNodePos rotateAt(BinNodePos);  //旋转调整

};


#endif //DATASTRUCTUREGIT_BST_H












