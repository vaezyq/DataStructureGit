//
// Created by 22126 on 2022/6/27.
//

#include "BinTree.h"
#include <iostream>

template<typename T>
BinNode<T> *BinTree<T>::insertAsLc(const T &e, BinNode<T> *pos) {
    ++_size;   //更新节点规模
    pos->insertAsLc(e);  //作为左孩子插入
    updateHeightAbove(pos); //更新从pos开始的所有节点高度
    return pos->lc;   //返回新插入的左孩子
}

template<typename T>
BinNode<T> *BinTree<T>::insertAsRc(BinNode<T> *pos, const T &e) {
    ++_size; //更新节点规模
    pos->insertAsRc(e); //作为右孩子插入
    updateHeightAbove(pos); //更新从pos开始的所有节点高度
    return pos->rc; //返回新插入的右孩子
}


#define stature(p) (p)? p->heigth :-1    //如果是空树，即p=nullpter,默认高度为-1

template<typename T>
int BinTree<T>::updateHeight(BinNode<T> *x) {
    return x = 1 + std::max(stature(x->lc), stature(x->rc));
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
BinNode<T> *BinTree<T>::attachAsLc(BinTree<T> *&S, BinNode<T> *x) {
    if ((x->lc = S->_root) != nullptr) {
        x->lc->parent = x;
    }
    _size += x->size();
    updateHeightAbove(x);
    //释放树
    S->_root = nullptr;
    S->_size = 0;
    delete S;    //这一步的作用是什么

    return x;
}

template<typename T>
BinNode<T> *BinTree<T>::attachAsRc(BinNode<T> *x, BinTree<T> *&S) {
    if ((x->rc = S->_root) != nullptr) {
        x->rc->parent = x;
    }
    _size += S->size();
    updateHeightAbove(x);
    //释放树
    S->_root = nullptr;
    S->_size = 0;
    delete S;    //这一步的作用是什么
    return x;


}


template<typename T>
int BinTree<T>::remove(BinNode<T> *pos) {
    if (BinNode<T>::HasParent(pos)) {
        BinNode<T>::IsLChild(pos) ? pos->parent->lc = nullptr : pos->parent->rc = nullptr;
    }
    updateHeightAbove(pos->parent);
    auto n = removeAt(pos);
    _size -= n;
    return n;
}

template<typename T>
int BinTree<T>::removeAt(BinNode<T> *pos) {
    if (pos == nullptr) return 0;
    int n = 1 + removeAt(pos->lc) + removeAt(pos->rc);
    delete pos;
    return n;

}

template<typename T>
BinTree<T> *BinTree<T>::secede(BinNode<T> *pos) {
    if (BinNode<T>::HasParent(pos)) {
        BinNode<T>::IsLChild(pos) ? pos->parent->lc = nullptr : pos->parent->rc = nullptr;
    }
    updateHeightAbove(pos);
    BinTree<T> *S = new BinTree<T>;
    S->_root = pos;
    pos->parent = nullptr;
    S->_size = pos->size();
    _size -= S->_size;
    return S;
}















//#define stature(p) ((p)?(p)->height:-1)     //节点高度：空树:-1
//
//template<typename T>
//int BinTree<T>::updateHeight(BinNode<T> *x) {
//    return x->height = 1 + max(stature(x->lc), stature(x->rc));
//}
//
//template<typename T>
//void BinTree<T>::updateHeightAbove(BinNode<T> *x) {
//    while (x) {
//        updateHeight(x);
//        x = x->parent;
//    }
//
//}
//
//template<typename T>
//BinNode<T> *BinTree<T>::insertAsRoot(const T &e) {
//    _size = 1;
//    return _root = new BinNode<T>(e);
//}
//
//template<typename T>
//BinNode<T> *BinTree<T>::insertAsLc(const T &e, BinNode<T> *pos) {
//    _size++;
//    pos->insertAsLc(e);
//    updateHeightAbove(pos);
//    return pos->lc;
//}
//
//template<typename T>
//BinNode<T> *BinTree<T>::insertAsRc(BinNode<T> *pos, const T &e) {
//    _size++;
//    pos->insertAsRc(e);
//    updateHeightAbove(pos);
//    return pos->rc;
//}
//
//template<typename T>
//BinNode<T> *BinTree<T>::attachAsLc(BinTree<T> *&t, BinNode<T> *x) {
//    if ((x->lc = t->_root) != nullptr) {
//        x->lc->parent = x;
//    }
//    _size += t->_size;
//    updateHeightAbove(x);
//    remove(t->_root);
//    return x;
//}
//
//template<typename T>
//BinNode<T> *BinTree<T>::attachAsRc(BinNode<T> *x, BinTree<T> *&t) {
//    if ((x->rc = t->_root) != nullptr) {
//        x->rc->parent = x;
//    }
//    _size += t->_size;
//    updateHeightAbove(x);
//    remove(t->_root);
//    return x;
//}
//
//template<typename T>
//int BinTree<T>::remove(BinNode<T> *pos) {
//    if (BinNode<T>::HasParent(pos)) {
//        BinNode<T>::IsLChild(pos) ? pos->parent->lc = nullptr : pos->parent->rc = nullptr;
//    }
//    updateHeightAbove(pos->parent);
//
//    int n = removeAt(pos);
//    _size -= n;
//    return n;
//
//}
//
//template<typename T>
//static int BinTree<T>::removeAt(BinNode<T> *pos) {
//    if (pos == nullptr) return 0; //空树
//    int n = 1 + removeAt(pos->lc) + removeAt(pos->rx);
//    return n;
//}
//
//template<typename T>
//BinTree<T> *BinTree<T>::secede(BinNode<T> *pos) {
//    if (BinNode<T>::HasParent(pos)) {
//        BinNode<T>::IsLChild(pos) ? pos->parent->lc = nullptr : pos->parent->rc = nullptr;
//    }
//    updateHeightAbove(pos->parent);
//    BinTree<T>* S=new BinTree<T>;
//    S->_root=pos;
//    pos->parent= nullptr;
//    S->_size=pos->size();
//    _size=S->_size;
//    return S;
//}
//
//




































