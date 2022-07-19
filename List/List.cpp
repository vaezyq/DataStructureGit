//
// Created by 22126 on 2022/6/12.
//

#include "List.h"
#include "ListNode.h"
#include<iostream>


template<typename T>
void List<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    trailer->pred = header;
    _size = 0;
}

template<typename T>
int List<T>::clear() {
    auto oldSize{_size};
    auto p = first();
    while (p != trailer) {
        p = p->succ;
        remove(p->pred);
    }
    return oldSize;
}

template<typename T>
void List<T>::copyNodes(ListNode<T> *p, int n) {
    while (n--) {
        trailer->insertAsPred(p->data);
        p = p->succ;
    }
}

template<typename T>
void List<T>::insertionSort(ListNode<T> *p, int n) {
    for (auto r = 0; r < n; ++r) {
        insertB(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template<typename T>
void List<T>::selectionSort(ListNode<T> *p, int n) {
    auto head = p->pred, tail = p;
    for (auto i = 0; i < n; ++i) {
        tail = tail->succ;
    }
    while (1 < n) {
        insertB(tail, remove(selectMax(head->succ, n)));
        tail = tail->pred;
        n--;
    }
}

// 注意这里p要使用引用(理由？)
template<typename T>
void List<T>::mergeSort(ListNode<T> *&p, int n) {

    if (n < 2) return;


    std::cout << std::endl;
//    std::cout<<n;
//    std::cout << std::endl;

    auto mi = n >> 1;
    auto q{p};
    for (auto i = 0; i < mi; ++i) {
        q = q->succ;
    }
    mergeSort(p, mi);
    mergeSort(q, n - mi);
    p = merge(p, mi, *this, q, n - mi);


}


template<typename T>
ListNode<T> *List<T>::merge(ListNode<T> *p, int n, List<T> &L, ListNode<T> *q, int m) {
    auto pp = p->pred;

    while ((0 < m) && (q != p)) {
        if ((0 < n) && (p->data <= q->data)) {
            p = p->succ;
            n--;
        } else {
            insertB(p, L.remove((q = q->succ)->pred));
            m--;
        }
    }
    return pp->succ;
}

template<typename T>
List<T>::List(List<T> &L) {
    init();
    copyNodes(L.first(), L._size);
    _size = L._size;
}

template<typename T>
List<T>::List(const List<T> &L, int r, int n) {
    init();
    auto p = L.first();
    while (r--) {
        p = p->succ;
    }
    copyNodes(p, n);
    _size = n;
}

template<typename T>
List<T>::List(ListNode<T> *p, int n) {
    init();
    copyNodes(p, n);
    _size = n;
}

template<typename T>
List<T>::~List() {
    clear();
    delete header;
    delete trailer;
}

template<typename T>
int List<T>::size() const {
    return _size;
}

template<typename T>
bool List<T>::isEmpty() const {
    return _size == 0;
}

template<typename T>
T &List<T>::operator[](int r) const {
    auto p = first();
    while (r--) {
        p = p->succ;
    }
    return p->data;
}

template<typename T>
ListNode<T> *List<T>::first() const {
    return header->succ;
}

template<typename T>
ListNode<T> *List<T>::last() const {
    return trailer->pred;
}

template<typename T>
bool List<T>::valid(ListNode<T> *p) {
    for (auto x = first(); x != trailer; x = x->succ) {
        if (p == x) return true;
    }
    return false;
}

template<typename T>
int List<T>::disordered() {
    auto count{0};
    for (auto p = first()->succ; p != trailer; p = p->succ) {
        if (p->data < p->pred->data) count++;
    }
    return count;
}

template<typename T>
ListNode<T> *List<T>::find(const T &e) {
    return find(e, _size, trailer);
}

template<typename T>
ListNode<T> *List<T>::find(const T &e, int n, ListNode<T> *p) {
    while (n--) {
        if ((p = p->pred)->data == e) break;
    }
    return p;
}

template<typename T>
ListNode<T> *List<T>::search(const T &e) {
    return find(e, _size, trailer);
}

template<typename T>
ListNode<T> *List<T>::search(const T &e, int n, ListNode<T> *p) {
    return find(e, n, p);
}

template<typename T>
ListNode<T> *List<T>::selectMax(ListNode<T> *p, int n) {
    auto max{p->data};
    auto q{p};
    while (n--) {
        if (max < p->data) {
            max = p->data;
            q = p;
        }
        p = p->succ;
    }
    return q;
}

template<typename T>
ListNode<T> *List<T>::selectMax() {
    return selectMax(first(), _size);
}

template<typename T>
ListNode<T> *List<T>::insertAsFirst(const T &e) {
    _size++;
    return header->insertAsSucc(e);
}

template<typename T>
ListNode<T> *List<T>::insertAsLast(const T &e) {
    _size++;
    return trailer->insertAsPred(e);
}

template<typename T>
ListNode<T> *List<T>::insertA(ListNode<T> *p, const T &e) {
    _size++;
    return p->insertAsSucc(e);
}

template<typename T>
ListNode<T> *List<T>::insertB(ListNode<T> *p, const T &e) {
    _size++;
    return p->insertAsPred(e);
}

template<typename T>
T List<T>::remove(ListNode<T> *p) {
    auto data = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return data;
}

template<typename T>
void List<T>::merge(List<T> &L) {
    merge(first(), _size, L, L.first(), L._size);
}

template<typename T>
void List<T>::sort(ListNode<T> *p, int n) {
    switch (3) {
        case 0:
            insertionSort(p, n);
            break;
        case 1:
            selectionSort(p, n);
            break;
        case 2:
        default:
            mergeSort(p, n);
            break;
    }
}

template<typename T>
void List<T>::sort() {
    sort(first(), _size);
}

template<typename T>
int List<T>::deduplicate() {
    auto n{1}, oldSize{_size};
    ListNodePoi x;
    for (auto p = first()->succ; p != trailer; p = p->succ) {
        if ((x = find(p->data, n, p)) != header) remove(x);
        else n++;
    }
    return oldSize - _size;
}

template<typename T>
int List<T>::uniquify() {

    return deduplicate();
}

template<typename T>
void List<T>::reverse() {
    for (auto p = first(), q = last(); (p != q) && (q->succ != p); p = p->succ, q = q->pred)
        std::swap(p->data, q->data);
}


template
class List<int>;


