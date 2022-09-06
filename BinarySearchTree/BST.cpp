//
// Created by 22126 on 2022/8/20.
//

#include "BST.h"

template<typename T>
BinNode<T> *&BST<T>::search(const T &e) {    //迭代版本
    if (!this->_root || e == this->_root->data) {   //空树，或者恰好在树根处命中
        _hot = nullptr;
        return this->_root;
    }
    for (_hot = this->_root;;) {
        BinNodePos&v = (e < _hot->data) ? _hot->lc : _hot->rc;    //深入下一层
        if (!v || e == v->data) {      //命中或者抵达叶子也没有找到，随即返回
            return v;       //返回目标节点位置的引用，以便后续的插入、删除操作
        }
        _hot = v; //无论命中或者失败，_hot均指向v的父亲节点。(当v是根时，hot为nullpter)
    }
}

template<typename T>
BinNode<T> *&BST<T>::searchIn(BinNodePos&v, const T &e, BinNodePos&hot) {      //递归版本
    if (!v || v->data == e) {        //递归基，在节点v处命中
        return v;
    }
    hot = v;
    return searchIn((e < v->data ? v->lc : v->rc), e, hot);   //深入一层递归查找
}

template<typename T>
BinNode<T> *BST<T>::insert(const T &e) {       //将关键码e插入BST树中
    BinNodePos&x = search(e);
    if (x) {   //目标关键码不存在
        return x;
    }
    x = new BinNode<T>(e, _hot);    //创建一个新节点，关键码是e，父亲为_hot
    this->_size++;    //更新全树规模
    this->updateHeightAbove(x);      //更新x与其祖先的高度
    return x;
}

template<typename T>
bool BST<T>::remove(const T &e) {
    BinNodePos&x = search(e); //首先定位到需要被删除的节点
    if (!x) {   //要被删除的节点不存在
        return false;
    }
    remove(x, _hot); //实施删除
    this->_size--;     //更新全树规模
    this->updateHeightAbove(_hot);     //更新全树高度
    return true;
}

template<typename T>
BinNode<T> *BST<T>::removeAt(BinNode<T> *&x, BinNode<T> *&hot) {
    auto w = x;    //实际被删除的节点，初始值等于x
    BinNodePos succ = nullptr;   //被删除节点的接替者(即删除后，哪个节点会接替原来的位置)
    if (!BinNode<T>::HasLChild(x)) {   //左子树为空
        succ = x = x->rc;    //接替的节点为x的右子树节点
    } else if (!BinNode<T>::HasRChild(x)) {    //右子树为空
        succ = x = x->lc;   //接替的节点为x的左子树节点
    } else {
        w = w->succ();  //调用得到w的中序遍历后缀
        swap(w->data, x->data);   //交换w,x的数据；进而只需要实际删除w
        auto u = w->parent;
        (u == x ? u->rc : u->lc) = succ = w->rc; //兼顾特殊情况：u可能就是x

    }
    hot = w->parent; //实际被删除节点的父亲
    if (succ) {     //如果接替节点存在(左右子树都为空时接替节点也是空)
        succ->parent = hot;   //接替节点的父亲设置为原删除节点的父亲
        return succ;   //返回接替者
    }
}

template<typename T>
BinNode<T> *
BST<T>::connect34(BinNode<T> *a, BinNode<T> *b, BinNode<T> *c, BinNode<T> *T0, BinNode<T> *T1, BinNode<T> *T2,
                  BinNode<T> *T3) {
    a->lc = T0;
    if (T0) {
        T0->parent = a;
    }
    a->rc = T1;
    if (T1) {
        T1->parent = a;
    }
    this->updateHeight(a);

    c->lc = T2;
    if (T2) {
        T2->parent = c;
    }
    c->rc = T3;
    if (T3) {
        T3->parent = c;
    }
    this->updateHeight(c);

    b->lc = a;
    a->parent = b;
    b->rc = c;
    c->parent = b;
    this->updateHeight(b);
    return b;  //返回该子树的根节点
}

template<typename T>
BinNode<T> *BST<T>::rotateAt(BinNode<T> *v) {
    auto p = v->parent, g = p->parent;
    if (BinNode<T>::IsLChild(p)) { //zig
        if (BinNode<T>::IsLChild(v)) { //zig-zig
            p->parent = g->parent;
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        } else {  //zig-zag
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    } else {  //zag
        if(BinNode<T>::IsRChild(v)){  //zag-zag

        } else{  //zag-zig

        }



    }
}




