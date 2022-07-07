//
// Created by 22126 on 2022/6/27.
//

#ifndef DATASTRUCTUREGIT_BINTREE_H
#define DATASTRUCTUREGIT_BINTREE_H

#include "BinNode.h"


template<typename T>
class BinTree {
protected:
    int _size;   //规模

    BinNodePos _root;  //根节点

    virtual int updateHeight(BinNodePos x);  //更新节点x的高度

    void updateHeightAbove(BinNodePos x);    //更新节点x及其祖先的高度

public:
    BinTree() : _size(0), _root(nullptr) {}

    ~BinTree() {
        if (0 < _size)remove(_root);
        delete _root;
    }

    int size() const { return _size; }

    bool isEmpty() const { return _root == nullptr; }

    BinNodePos root() const { return _root; }  //返回树根

    BinNodePos insertAsRoot(T const &e);   //插入根节点

    BinNodePos insertAsLc(T const &e, BinNodePos pos); //e作为pos的左孩子插入

    BinNodePos insertAsRc(BinNodePos pos, T const &e);   //e作为pos的右孩子插入

    BinNodePos attachAsLc(BinTree<T> *&S, BinNodePos x); //t作为x的左子树插入

    BinNodePos attachAsRc(BinNodePos x, BinTree<T> *&S); //t作为x的右子树插入

    int remove(BinNodePos pos); //子树删除

    int removeAt(BinNodePos pos); //子树删除

    BinTree<T> *secede(BinNodePos pos);  //将子树pos摘除，并返回这颗独立的树

    template<class VST>
    void travLevel(VST &visit) {   //子树层次遍历
        if (_root) {
            _root->travLevel(visit);
        }
    }

    template<class VST>
    void travPre(VST &visit) {   //子树先序遍历
        if (_root) {
            _root->travPre(visit);
        }
    }

    template<class VST>
    void travIn(VST &visit) {   //子树中序遍历
        if (_root) {
            _root->travIn(visit);
        }
    }

    template<class VST>
    void travPost(VST &visit) {   //子树后序遍历
        if (_root) {
            _root->travPost(visit);
        }
    }

    bool operator<(BinTree<T> const &t) {
        return _root & t._root && (_root < t._root);
    }

    bool operator==(BinTree<T> const &t) {
        return _root & t._root && (_root == t._root);
    }

};


#endif //DATASTRUCTUREGIT_BINTREE_H














