//
// Created by 22126 on 2022/6/27.
//

#include "BinTree.h"

#define stature(p) ((p)?(p)->height:-1)     //节点高度：空树:-1

template<typename T>
int BinTree<T>::updateHeight(BinNode<T> *x) {
    return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNode<T> *x) {
    while (x) {
        updateHeight(x);
        x = x->parent;
    }

}

template<typename T>
BinNode<T> *BinTree<T>::insertAsRoot(const T &e) {
    _size = 1;
    return _root = new BinNode<T>(e);
}

template<typename T>
BinNode<T> *BinTree<T>::insertAsLc(const T &e, BinNode<T> *pos) {
    _size++;
    pos->insertAsLc(e);
    updateHeightAbove(pos);
    return pos->lc;
}

template<typename T>
BinNode<T> *BinTree<T>::insertAsRc(BinNode<T> *pos, const T &e) {
    _size++;
    pos->insertAsRc(e);
    updateHeightAbove(pos);
    return pos->rc;
}

template<typename T>
BinNode<T> *BinTree<T>::attachAsLc(BinTree<T> *&t, BinNode<T> *x) {
    if ((x->lc = t->_root) != nullptr) {
        x->lc->parent = x;
    }
    _size += t->_size;
    updateHeightAbove(x);
    remove(t->_root);
    return x;
}

template<typename T>
BinNode<T> *BinTree<T>::attachAsRc(BinNode<T> *x, BinTree<T> *&t) {
    if ((x->rc = t->_root) != nullptr) {
        x->rc->parent = x;
    }
    _size += t->_size;
    updateHeightAbove(x);
    remove(t->_root);
    return x;
}

template<typename T>
int BinTree<T>::remove(BinNode<T> *pos) {
    if (BinNode<T>::HasParent(pos)) {
        BinNode<T>::IsLChild(pos) ? pos->parent->lc = nullptr : pos->parent->rc = nullptr;
    }
    updateHeightAbove(pos->parent);

    int n = removeAt(pos);
    _size -= n;
    return n;

}

template<typename T>
static int BinTree<T>::removeAt(BinNode<T> *pos) {
    if (pos == nullptr) return 0; //空树
    int n = 1 + removeAt(pos->lc) + removeAt(pos->rx);
    return n;
}

template<typename T>
BinTree<T> *BinTree<T>::secede(BinNode<T> *pos) {
    if (BinNode<T>::HasParent(pos)) {
        BinNode<T>::IsLChild(pos) ? pos->parent->lc = nullptr : pos->parent->rc = nullptr;
    }
    updateHeightAbove(pos->parent);
    BinTree<T>* S=new BinTree<T>;
    S->_root=pos;
    pos->parent= nullptr;
    S->_size=pos->size();
    _size=S->_size;
    return S;
}






































