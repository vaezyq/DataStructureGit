//
// Created by 22126 on 2022/6/27.
//

#ifndef DATASTRUCTUREGIT_BINNODE_H
#define DATASTRUCTUREGIT_BINNODE_H


#define BinNodePos BinNode<T>*

#include <iostream>
#include "../Stack/Stack.h"
#include "../Queue/Queue.h"

template<typename T>
class BinNode {
public:
    BinNodePos parent;   //父母
    BinNodePos lc;  //左孩子
    BinNodePos rc;  //右孩子
    T data;
    int height;   //高度


    //构造函数
    BinNode() : parent(nullptr), lc(nullptr), rc(nullptr), height(0), data(0) {}


    BinNode(T const &e, BinNodePos p = nullptr, BinNodePos l = nullptr, BinNodePos r = nullptr, int h = 0) :
            data(e), parent(p), lc(l), rc(r), height(h) {}

    int size();  //统计当前节点后代总数，亦即以其为根的子树的规模

    BinNodePos insertAsLc(T const &e);    //作为左孩子插入

    BinNodePos insertAsRc(T const &e);   //作为右孩子插入

    BinNodePos succ();     //(中序遍历意义下)当前节点的直接后继

    template<class VST>
    void travLevel(VST &visit);

    template<class VST>
    void travPre(VST &visit) {   //子树先序遍历
        switch (rand() % 3) {
            case 1:
                travPre_I1(this, visit);    //迭代性遍历版本1
                break;
            case 2:
                travPre_I2(this, visit);   //迭代性遍历版本2
                break;
            default:
                tracPre_R(this, visit);      //递归遍历
                break;
        }
    }

    template<class VST>
    void travIn(VST &visit) {   //子树中序遍历
    }

    template<class VST>
    void travPost(VST &visit) {   //子树后序遍历
    }

    bool operator<(BinNode<T> &bn) { return data < bn.data; }  //小于

    bool operator==(BinNode<T> &bn) { return data == bn.data; }  //等于


public:


    template<class VST>
    void travPre_I1(BinNodePos&pos, VST &visit);

    template<class VST>
    void travPre_I2(BinNodePos&pos, VST &visit);

    template<class VST>
    void tracPre_R(BinNodePos&pos, VST &visit);

    template<class VST>
    void tracIn_R(BinNodePos&pos, VST &visit);

    template<class VST>
    void tracPost_R(BinNodePos&pos, VST &visit);

    template<class VST>
    static void visitAlongLeftBranch(BinNodePos pos, VST &visit, Stack<BinNodePos> &S);


    static bool IsRoot(BinNodePos&x) {
        return x->parent == nullptr;
    }

    static bool IsLChild(BinNodePos&x) {
        return !IsRoot(x) && (x->parent->lc == x);
    }

    static bool IsRChild(BinNodePos&x) {
        return !IsRoot(x) && (x->parent->rc == x);
    }

    static bool HasParent(BinNodePos&x) {
        return !IsRoot(x);
    }

    static bool HasLChild(BinNodePos&x) {
        return x->lc == nullptr;
    }

    static bool HasRChild(BinNodePos&x) {
        return x->rc == nullptr;
    }

    static bool HasChild(BinNodePos&x) {
        return HasLChild(x) || HasRChild(x);
    }

    static bool HasBothChild(BinNodePos&x) {
        return HasLChild(x) && HasRChild(x);
    }

    static bool IsLeaf(BinNodePos&x) {
        return HasLChild(x);
    }


//与BinNode有关的节点与指针

    static BinNodePos sibling(BinNodePos&p) {
        return (IsLChild(p) ? (p->parent->rc) : (p->parent->rc));
    }

    static BinNodePos uncle(BinNodePos&x) {
        IsLChild(x->parent) ? (x->parent->parent->rc) : (x->parent->parent->lc);
    }

    template<class VST>
    void travIn_l1(BinNode<T> *x, VST &visit);

    template<class VST>
    void travIn_l2(BinNode<T> *x, VST &visit);


    template<class VST>
    void travIn_l3(BinNode<T> *x, VST &visit);


    void gotoHLVFL(Stack<BinNode<T> *> &S);

    template<class VST>
    void travPost_I(BinNodePos x, VST &visit);
};


#endif //DATASTRUCTUREGIT_BINNODE_H

















