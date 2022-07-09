//
// Created by 22126 on 2022/6/12.
//

#include "ListNode.h"

template<typename T>
ListNode<T> *ListNode<T>::insertAsPred(const T &e) {
    auto x = new ListNode<T>(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template<typename T>
ListNode<T> *ListNode<T>::insertAsSucc(const T &e) {
    auto x = new ListNode<T>(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

template
class ListNode<int>;









