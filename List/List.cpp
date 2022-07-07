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
    header->pred = nullptr;
    trailer->succ = nullptr;
    trailer->pred = header;
    _size = 0;
}

template<typename T>
int List<T>::clear() {

    int oldSize = _size;
    while (0 < _size) {
        remove(header->succ);
    }
    return oldSize;
}

template<typename T>
void List<T>::copyNodes(ListNode<T> *p, int n) {
    init();
    while (n--) {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template<typename T>
void List<T>::insertionSort(ListNode<T> *p, int n) {
    for (int r = 0; r < n; ++r) {
        insertA(search(p->data, r, p), p->data);
    }
    p = p->succ;
    remove(p->pred);
}

template<typename T>
void List<T>::selectionSort(ListNode<T> *p, int n) {
    ListNodePoi tail = p;
    ListNodePoi head = p->pred;
    for (int i = 0; i < n; ++i) {
        tail = tail->succ;
    }
    while (1 < n) {
        ListNodePoi max = selectMax(head->succ, n);
        insertB(tail, remove(max));
        tail = tail->pred;
        n--;
    }
}

template<typename T>
void List<T>::mergeSort(ListNode<T> *p, int n) {
    if (n <= 1) return;
    int m = n >> 1;
    ListNodePoi q = p;
    for (int i = 0; i < m; ++i) {
        q = q->succ;
    }
    mergeSort(p, m);
    mergeSort(q, n - m);
    merge(p, m, *this, q, n - m);

}

template<typename T>
void List<T>::merge(ListNode<T> *p, int n, List<T> &L, ListNode<T> *q, int m) {
    while (m > 0) {
        if ((n > 0) && (p->data <= q->data)) {
            if (p->succ == q) break;
            p = p->succ;
            n--;
        } else {
            insertB(p, L.remove((q = q->succ)->pred));
            m--;
        }
    }
}

template<typename T>
List<T>::List(List<T> &L) {
    init();
    copyNodes(L.first(), L._size);
}

template<typename T>
List<T>::List(const List<T> &L, int r, int n) {
    init();
    auto p = L.first();
    for (auto i = 0; i < r; ++i) {
        p = p->succ;
    }
    copyNodes(p, n);
}

template<typename T>
List<T>::List(ListNode<T> *p, int n) {
    init();
    copyNodes(p, n);
}

template<typename T>
List<T>::~List() {
    clear();
    delete trailer;
    delete header;
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
    for (auto i = 0; i < r; ++i) {
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
    auto q = header;
    for (auto i = 0; i < _size; ++i) {
        if ((q = q->succ) == p) return true;
    }
    return false;
}

template<typename T>
int List<T>::disordered() {
    auto n{0};
    auto p = first();
    for (auto i = 0; i < _size - 1; ++i) {
        n += ((p->data) > (p->succ->data));
        p = p->succ;
    }
    return n;
}

template<typename T>
ListNode<T> *List<T>::find(const T &e) {
    return find(e, _size, trailer);
}

template<typename T>
ListNode<T> *List<T>::find(const T &e, int n, ListNode<T> *p) {
    while ((n--) >= 0) {
        if ((p = p->pred)->data == e) break;
    }
    return p;
}

template<typename T>
ListNode<T> *List<T>::search(const T &e) {
    return find(e);
}

template<typename T>
ListNode<T> *List<T>::search(const T &e, int n, ListNode<T> *p) {
    return find(e, n, p);
}

template<typename T>
ListNode<T> *List<T>::selectMax(ListNode<T> *p, int n) {
    auto q{p};
    while (--n) {
        if (((p = p->succ)->data) >= q->data) q = p;
    }
    return q;
}

template<typename T>
ListNode<T> *List<T>::selectMax() {
    return selectMax(first(), _size);
}

template<typename T>
ListNode<T> *List<T>::insertAsFirst(const T &e) {
    ++_size;
    return header->insertAsSucc(e);
}

template<typename T>
ListNode<T> *List<T>::insertAsLast(const T &e) {
    ++_size;
    return trailer->insertAsPred(e);
}

template<typename T>
ListNode<T> *List<T>::insertA(ListNode<T> *p, const T &e) {
    ++_size;
    return p->insertAsSucc(e);
}

template<typename T>
ListNode<T> *List<T>::insertB(ListNode<T> *p, const T &e) {
    ++_size;
    return p->insertAsPred(e);
}

template<typename T>
T List<T>::remove(ListNode<T> *p) {
    auto data = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    --_size;
    return data;
}

template<typename T>
void List<T>::merge(List<T> &L) {
    merge(first(), _size, L, L.first(), L._size);
}

template<typename T>
void List<T>::sort(ListNode<T> *p, int n) {
    switch (rand() % 2) {
        case 0:
            selectionSort(p, n);
            break;
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
    if (_size < 2) return 0;
    int r = 0;
    auto p = first();
    int oldSize = _size;
    while (trailer != (p = p->succ)) {
        auto q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldSize - r;
}

template<typename T>
int List<T>::uniquify() {
    deduplicate();
}

template<typename T>
void List<T>::reverse() {

    for (auto p = header, q = trailer; (p->succ) != q; p = p->succ, q = q->pred) {
        std::swap(p->data, q->data);
    }
}


//template<typename T>
//void List<T>::traverse(void (*visit)(T &)) {
//    auto p = header;
//    for (auto i = 0; i < _size; ++i) {
//        visit((p = p->succ)->data);
//    }
//}
//
//template<typename T>
//template<typename VST>
//void List<T>::traverse(VST &visit) {
//    auto p = header;
//    for (auto i = 0; i < _size; ++i) {
//        visit((p = p->succ)->data);
//    }
//}





























//template<typename T>
//void List<T>::init() {
//
//    header = new ListNode<T>;
//    trailer = new ListNode<T>;
//    header->pred = nullptr;
//    header->succ = trailer;
//    trailer->pred = header;
//    trailer->succ = nullptr;
//    _size = 0;
//}
//
//
//template<typename T>
//T &List<T>::operator[](int index) const {
//    auto p = header;
//    for (auto i = 0; i < index; ++i) {
//        p = p->succ;
//    }
//    return p->data;
//}
//
//template<typename T>
//ListNode<T> *List<T>::find(const T &e, int n, ListNode<T> *p) {
//    //寻找p的n个真前驱元素是否存在e,这里是不包含p的，也就是p可以为trailer
//    while (0 < n--) {
//        if (e == (p->succ)->data) {
//            return p;
//        }
//    }
//    return nullptr;
//}
//
//template<typename T>
//ListNode<T> *List<T>::find(const T &e) {
//    return find(e, _size, trailer);
//}
//
//template<typename T>
//ListNode<T> *List<T>::insertAsFirst(const T &e) {
//    _size++;
//    return header->insertAsSucc(e);
//}
//
//template<typename T>
//ListNode<T> *List<T>::insertAsLast(const T &e) {
//    _size++;
//    return trailer->insertAsPred(e);
//}
//
//template<typename T>
////在节点p之后插入元素e
//ListNode<T> *List<T>::insertA(ListNode<T> *p, const T &e) {
//    _size++;
//    return p->insertAsSucc(e);
//}
//
//template<typename T>
//ListNode<T> *List<T>::insertB(ListNode<T> *p, const T &e) {
//    _size++;
//    return p->insertAsPred(e);
//}
//
//template<typename T>
//void List<T>::copyNodes(ListNode<T> *p, int n) {
//    init();
//    while (n--) {
//        insertAsLast(p->data);
//        p = p->succ;
//    }
//}
//
//template<typename T>
//ListNode<T> *List<T>::first() {
//    return header->succ;
//}
//
//template<typename T>
//ListNode<T> *List<T>::last() {
//    return trailer->pred;
//}
//
//
//template<typename T>
//List<T>::List(const List<T> &L) {
//    copyNodes(L.first(), L._size);
//}
//
//template<typename T>
//List<T>::List(const List<T> &L, int r, int n) {
//    copyNodes(L[r], n);
//}
//
//template<typename T>
//List<T>::List(ListNode<T> *p, int n) {
//    copyNodes(p, n);
//}
//
//template<typename T>
//T List<T>::remove(ListNode<T> *p) {
//    T e = p->data;
//    p->pred->succ = p->succ;
//    p->succ->pred = p->pred;
//    delete p;
//    _size--;
//    return e;
//}
//
//template<typename T>
//List<T>::~List() {
//    clear();
//    delete header;
//    delete trailer;
//}
//
//template<typename T>
//int List<T>::clear() {
//
//    int oldSize = _size;
//
//    while (_size) {
//        remove(header->succ);
//    }
//    return oldSize;
//
//
//}
//
//template<typename T>
//int List<T>::deduplicate() {
//    if (_size < 2) return 0;
//    int oldSize = _size;
//    int r = 0;
//    auto p = header;
//    while (trailer != (p = p->succ)) {
//        auto q = find(p->data, r, p);
//        q ? remove(q) : r++;
//    }
//    return oldSize - _size;
//}
//
//template<typename T>
//void List<T>::traverse(void (*visit)(T &)) {
//    for (auto p = first(); p != trailer; p = p->succ) {
//        visit(p->data);
//    }
//}
//
//template<typename T>
//template<typename VST>
//void List<T>::traverse(VST &visit) {
//    for (auto p = first(); p != trailer; p = p->succ) {
//        visit(p->data);
//    }
//}
//
//template<typename T>
//int List<T>::uniquify() {
//    if (_size < 2) return 0;
//    int oldSize = _size;
//    auto p = first();
//    decltype(p) q;
//    while (trailer != (q = p->succ)) {
//        if (p->data != q->data) {
//            p = q;
//        } else {
//            remove(q);
//        }
//    }
//    return oldSize - _size;
//
//}
//
//template<typename T>
//ListNode<T> *List<T>::search(const T &e, int n, ListNode<T> *p) {
//    while (n--) {
//        if ((p = p->pred)->data == e) break;
//    }
//    return p;
//}
//
//template<typename T>
//void List<T>::sort(ListNode<T> *p, int n) {
//    switch (rand() % 3) {
//        case 1:
//            insertionSort(p, n);
//            break;
//        case 2:
//            selectionSort(p, n);
//            break;
//        default:
//            mergeSort(p, n);
//            break;
//    }
//}
//
//template<typename T>
//void List<T>::insertionSort(ListNode<T> *p, int n) {
//    for (int r = 0; r < n; ++r) {
//        insertA(search((p->data, n)), p->data);
//        p = p->succ;
//        remove(p->pred);
//    }
//}
//
//template<typename T>
//void List<T>::selectionSort(ListNode<T> *p, int n) {
//    ListNodePoi hea000d = p->pred;
//    ListNode tail = p;
//    for (int i = 0; i < n; ++i) {
//        tail = tail->succ;
//    }
//
//    while ((1 < n)) {
//        ListNodePoi max = selectMax(header->succ, n);
//        insertB(tail, remove(max));
//        tail = tail->pred;
//        n--;
//    }
//
//}
//
//template<typename T>
//void List<T>::mergeSort(ListNode<T> *p, int n) {
//
//    if (n < 2) return;
//    int m = n >> 1;
//    auto q = p;
//    for (int i = 0; i < m; ++i) {
//        p = p->succ;
//    }
//    mergeSort(q, m);
//    mergeSort(p, n - m);
//    merge(p, m, *this, q, n - m);
//}
//
//template<typename T>
//void List<T>::merge(ListNode<T> *p, int n, List<T> &L, ListNode<T> *q, int m) {
//    auto pp = p->pred;
//    while (0 < m) {
//        if ((0 < n) && (p->data <= q->data)) {
//
//            // 这句话的作用是什么
//            if (q == (p = p->succ)) { break; }
//            n--;
//        } else {
//            insertB(p, L.remove((q = q->succ)->pred));
//            m--;
//        }
//    }
//    p = pp->succ;
//}
//
//template<typename T>
//int List<T>::size() const {
//    return _size;
//}
//
//template<typename T>
//bool List<T>::isEmpty() const {
//    return _size == 0;
//}




template
class List<int>;


