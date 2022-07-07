
#include "Vector.h"
#include "Fib.h"
#include <iostream>


template<typename T>
void Vector<T>::copyFrom(const T *A, int lo, int hi) {

    _capacity = (hi - lo) << 1;
    while (lo < hi) {
        _elem[_size++] = A[lo++];
    }
}

template<typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return; //不需要扩容
    auto oldElem = _elem;
    _capacity = std::max(DEFAULT_CAPACITY, _capacity);
    _elem = new T[_capacity <<= 1];
    for (auto i = 0; i < _size; ++i) {
        _elem[i] = oldElem[i];
    }
    delete[]oldElem;
}

template<typename T>
void Vector<T>::shrink() {
    if (_size > _capacity >> 2) return;
    auto oldElem = _elem;
    _elem = new T[_capacity = std::max(_capacity >> 1, DEFAULT_CAPACITY)];
    for (auto i = 0; i < _size; ++i) {
        _elem[i] = oldElem[i];
    }
    delete[]oldElem;
}

template<typename T>
bool Vector<T>::bubble(int lo, int hi) {
    bool sorted = true;
    while (lo < hi) {
        if (_elem[lo] > _elem[++lo]) {
            sorted = false;
            std::swap(_elem[lo], _elem[lo + 1]);
        }
        lo++;
    }
    return sorted;
}

template<typename T>
void Vector<T>::bubbleSort(int lo, int hi) {
    bool sorted = true;
    while (!sorted && hi > lo) {
        sorted = bubble(lo, hi--);
    }
}

template<typename T>
int Vector<T>::max(int lo, int hi) {
    auto maxElem = _elem[hi - 1];
    for (auto i = hi - 2; i >= lo; --i) {
        if (_elem[i] > maxElem) maxElem = _elem[i];
    }
    return maxElem;
}

template<typename T>
int Vector<T>::maxItem(int lo, int hi) {
    auto maxElem = _elem[hi - 1];
    auto maxIdx = hi - 1;
    for (auto i = hi - 2; i >= lo; --i) {
        if (_elem[i] > maxElem) {
            maxElem = _elem[i];
            maxIdx = i;
        }
    }
    return maxIdx;
}

template<typename T>
void Vector<T>::selectionSort(int lo, int hi) {
    for (auto i = lo; i < hi; ++i) {
        std::swap(_elem[hi - 1], maxItem(lo, hi));
        hi--;
    }
}

template<typename T>
void Vector<T>::merge(int lo, int mi, int hi) {
    auto loElem = new T[mi - lo];
    for (auto i = lo; i < mi; ++i) {
        loElem[i - lo] = _elem[i];
    }
    auto i = 0, j = mi, k = lo;
    while ((i < mi - lo) && (j < hi)) {
        if (loElem[i] > _elem[j]) {
            _elem[k++] = _elem[j++];
        } else {
            _elem[k++] = _elem[i++];
        }
    }
    while (i < mi - lo) {
        _elem[k++] = _elem[i++];
    }
}

template<typename T>
void Vector<T>::mergeSort(int lo, int hi) {
    if (lo >= hi) return;
    auto mi = (hi - lo) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template<typename T>
int Vector<T>::partition(int lo, int hi) {
    return 0;
}

template<typename T>
void Vector<T>::quickSort(int lo, int hi) {

}

template<typename T>
void Vector<T>::heapSort(int lo, int hi) {

}

template<typename T>
Vector<T>::Vector(int c, int s, T v) {
    _elem = new T[_capacity = c];
    for (auto i = 0; i < (_size = s); ++i) {
        _elem[i] = v;
    }
}

template<typename T>
Vector<T>::Vector(T *A, int n) {
    copyFrom(A, 0, n);
}

template<typename T>
Vector<T>::Vector(T *const A, int lo, int hi) {
    copyFrom(A, lo, hi);
}

template<typename T>
Vector<T>::Vector(const Vector<T> &V, int lo, int hi) {
    copyFrom(V._elem, lo, hi);
}

template<typename T>
Vector<T>::Vector(const Vector<T> &V) {
    copyFrom(V._elem, 0, V._size);
}

template<typename T>
Vector<T>::~Vector() {
    delete[]_elem;
}

template<typename T>
int Vector<T>::size() const {
    return _size;
}

template<typename T>
bool Vector<T>::isEmpty() const {
    return _size == 0;
}

template<typename T>
int Vector<T>::disordered() const {
    int outOfOrder = 0;
    for (auto i = 1; i < _size; ++i) {
        if (_elem[i - 1] > _elem[i]) outOfOrder++;
    }
    return outOfOrder;
}

template<typename T>
int Vector<T>::find(const T &e) const {
    return find(e, 0, _size);
}

template<typename T>
int Vector<T>::find(const T &e, int lo, int hi) const {
    auto idx = hi - 1;
    while (idx >= lo) {
        if (_elem[idx] == e) break;
    }
    return idx;
}

template<typename T>
int Vector<T>::search(const T &e, int lo, int hi) const {
    switch (rand() % 3) {
        case 0:
            binSearch(_elem, e, lo, hi);
            break;
        case 1:
            fibSearch(_elem, e, lo, hi);
            break;
        case 2:
            interpolationSearch(_elem, e, lo, hi);
            break;
    }
}

template<typename T>
T &Vector<T>::operator[](int i) {
    return _elem[i];
}

template<typename T>
int Vector<T>::remove(int r) {
    remove(r, r + 1);
}

template<typename T>
int Vector<T>::remove(int lo, int hi) {
    int remove_num = hi - lo;
    for (auto r = hi; r < _size; ++r) {
        _elem[lo++] = _elem[r];
    }
    _size = lo;
    shrink();
    return remove_num;
}

template<typename T>
int Vector<T>::insert(int r, const T &e) {
    expand();
    for (auto i = _size; i > r; --i) {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    ++_size;
    return _size;
}

template<typename T>
int Vector<T>::insert(const T &e) {
    return insert(e, _size);
}

template<typename T>
void Vector<T>::sort(int lo, int hi) {
    switch (rand() % 2) {
        case 0:
            selectionSort(lo, hi);
            break;
        case 1:
            mergeSort(lo, hi);
            break;
    }
}

template<typename T>
void Vector<T>::sort() {
    sort(0, _size);
}

template<typename T>
void Vector<T>::unsort(int lo, int hi) {
    for (auto i = _size - 1; i > 0; --i) {
        std::swap(_elem[rand() % i], _elem[i]);
    }
}

template<typename T>
int Vector<T>::duplicate() {
    int oldSize = _size;

    for (auto i = _size - 1; i > 0; --i) {
        auto res = find(_elem[i], 0, i);
        if (res < 0) remove(res);
    }
    return oldSize - _size;
}

template<typename T>
int Vector<T>::uniquify() {
    auto oldSize = _size;
    auto i = 0;
    for (auto j = 0; j < _size; j++) {
        if (_elem[i] != _elem[j]) {
            _elem[++i] = _elem[j];
        }
    }
    _size = ++i;
    return oldSize - _size;
}

template<typename T>
int Vector<T>::binSearch(T *S, const T &e, int lo, int hi) {


    while (true) {
        if (lo >= hi) return --lo;
        int mi = (hi + lo) >> 1;
        if (e < S[mi]) {
            hi = mi;
        } else {
            lo = mi + 1;
        }
    }
}

template<typename T>
int Vector<T>::fibSearch(T *S, const T &e, int lo, int hi) {


    while (true) {
        Fib fib(hi - lo);
        for (; fib.get() > (hi - lo); fib.prev());
        auto mi = fib.get() + lo - 1;
        if (S[mi] < e) {
            lo = mi + 1;
        } else if (S[mi] > e) {
            hi = mi - 1;
        } else {
            return mi;
        }
    }
}

template<typename T>
int Vector<T>::interpolationSearch(T *S, const T &e, int lo, int hi) {
    while (true){



    }


    return 0;
}























////
//// Created by 22126 on 2022/5/27.
////
//
//#include "Vector.h"
//#include "Fib.h"
//#include <cmath>
//#include <iostream>
//
//
//template<typename T>
//void Vector<T>::copyFrom(const T *A, int lo, int hi) {
//
//    _elem = new T[_capacity = 2 * (hi - lo)];
//
//    auto len = hi - lo;
//    for (_size = 0; _size < len; _size++, lo++) {
//        _elem[_size] = A[lo];
//    }
//}
//
//
//template<typename T>
//void Vector<T>::expand() {   //向量空间不足时扩容
//
//    if (_size < _capacity) return;  //不需要扩容
//    _capacity = std::max(_capacity, DEFAULT_CAPACITY);
//    auto oldElem = _elem;
//    _elem = new T[_capacity <<= 1];
//    for (auto i = 0; i < _size; ++i) {
//        _elem[i] = oldElem[i];
//    }
//    delete[]oldElem;    //注意最后删除旧指针
//}
//
//template<typename T>
//void Vector<T>::shrink() {
//
//    if (_capacity < DEFAULT_CAPACITY << 1) return;
//    if (_size << 2 > _capacity) return;
//    auto oldElem = _elem;
//    _elem = new T[_capacity >>= 1];
//
//    for (auto i = 0; i < _size; ++i) {
//        _elem[i] = oldElem[i];
//    }
//    delete[]oldElem;
//
//}
//
//template<typename T>
//bool Vector<T>::bubble(int lo, int hi) {
//
//    bool isSorted = true;
//    for (auto i = lo; i != --hi; ++i) {
//        if (_elem[i] > _elem[i++]) {
//            std::swap(_elem[i], _elem[i + 1]);
//            isSorted = false;
//        }
//    }
//    return isSorted;
//}
//
//
////  跳跃版
//template<typename T>
//void Vector<T>::bubbleSort(int lo, int hi) {
//    for (auto last = --hi; lo < hi; hi = last) {
//        for (auto i = last = lo; i < hi; ++i) {
//            if (_elem[i] > _elem[i + 1]) {
//                std::swap(_elem[i], _elem[i + 1]);
//                last = i;
//            }
//        }
//    }
//}
//
//
//template<typename T>
//int Vector<T>::max(int lo, int hi) {
//    auto maxElem = _elem[lo];
//    for (auto i = lo + 1; i < hi; ++i) {
//        if (maxElem < _elem[i]) {
//            maxElem = _elem[i];
//        }
//    }
//    return maxElem;
//}
//
//template<typename T>
//int Vector<T>::maxItem(int lo, int hi) {
//    auto maxCur = hi - 1;
//    while (hi-- > lo) {
//        if (_elem[hi] > _elem[maxCur]) {
//            maxCur = hi;
//        }
//    }
//    return maxCur;
//}
//
//
//template<typename T>
//void Vector<T>::selectionSort(int lo, int hi) {
//    auto elem = new T[hi - lo];
//    while (lo < --hi) {
//        std::swap(_elem[maxItem(lo, hi + 1)], _elem[hi]);
//    }
//}
//
//template<typename T>
//void Vector<T>::merge(int lo, int mi, int hi) {
//    T *A = _elem + lo;
//    int lb = mi - lo;
//    T *B = new T[lb];
//    for (int i = 0; i < lb; B[i] = A[i++]); //复制前子向量
//    int lc = hi - mi;
//    T *C = _elem + mi;
//    auto i = 0, j = 0, k = 0;
//    while ((j < lb) && (k < lc)) {
//        A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++];
//    }
//    while (j < lb) {
//        A[i++] = B[j++];
//    }
//    delete[]B;
//}
//
//
//template<typename T>
//void Vector<T>::mergeSort(int lo, int hi) {
//
//    if (hi - lo < 2) return;
//
//    int mi = (hi + lo) >> 1;
//    mergeSort(lo, mi);
//    mergeSort(mi, hi);
//    merge(lo, mi, hi);
//}
//
//
//template<typename T>
//Vector<T>::Vector(int c, int s, T v) {    //默认情况
//    _elem = new T[_capacity = c];
//    _size = s;
//    for (int i = 0; i < s; _elem[i++] = v);
//}
//
//
//template<typename T>
//Vector<T>::Vector(T *const A, int n) {
//    copyFrom(A, 0, n);
//}
//
//
//template<typename T>
//Vector<T>::Vector(T *const A, int lo, int hi) {
//    copyFrom(A, lo, hi);
//}
//
//template<typename T>
//Vector<T>::Vector(const Vector<T> &V, int lo, int hi) {
//    copyFrom(V._elem, lo, hi);
//}
//
//template<typename T>
//Vector<T>::Vector(Vector<T> const &V) {
//    copyFrom(V._elem, 0, V._size);
//}
//
//template<typename T>
//Vector<T>::~Vector() {
//    delete[] _elem;
//}
//
//
//template<typename T>
//int Vector<T>::size() const {
//    return _size;
//}
//
//template<typename T>
//bool Vector<T>::isEmpty() const {
//    return _size == 0;
//}
//
//
//template<typename T>
//int Vector<T>::disordered() const {
//
//    auto n{0};
//    for (auto i = 1; i < _size; ++i) {
//        n += (_elem[i - 1] > _elem[i]);
//    }
//    return n;
//}
//
//template<typename T>
//int Vector<T>::find(T const &e) const {
//    return find(e, 0, _size);
//}
//
//template<typename T>
//int Vector<T>::find(const T &e, int lo, int hi) const {
//
//    while ((lo < hi--) && (_elem[hi] != e));
//    return hi;
//}
//
//template<typename T>
//int Vector<T>::search(const T &e, int lo, int hi) const {
//    switch (rand() % 2) {
//        case 0:
//            std::cout << 1;
//            return binSearch(_elem, e, lo, hi);
//            break;
//
//        case 1:
//            std::cout << 2;
//            return fibSearch(_elem, e, lo, hi);
//            break;
//
//        default:
//            std::cout << 3;
//            return interpolationSearch(_elem, e, lo, hi);
//            break;
//    }
//}
//
//template<typename T>
//T &Vector<T>::operator[](int i) {
//    return _elem[i];
//}
//
//template<typename T>
//Vector<T> Vector<T>::operator=(const Vector<T> &v) {
//    delete[]_elem;
//    copyFrom(v._elem, 0, _size);
//    return *this;
//}
//
//template<typename T>
//int Vector<T>::remove(int r) {
//
//    auto e = _elem[r];
//    remove(r, r + 1);
//    return e;
//}
//
//template<typename T>
//int Vector<T>::remove(int lo, int hi) {
//
//    if (hi == lo) return 0;
//    while (hi < _size) {
//        _elem[lo++] = _elem[hi++];
//    }
//    _size = lo;
//    return hi - lo;
//}
//
//
//template<typename T>
//int Vector<T>::insert(int r, const T &e) {
//    expand();// 查看是否需要扩容
//    for (auto i = _size; i > r; --i) {
//        _elem[i] = _elem[i - 1];
//    }
//    _elem[r] = e;
//    _size++;
//    return r;
//}
//
//template<typename T>
//int Vector<T>::insert(const T &e) {
//    return insert(_size, e);
//}
//
//
//template<typename T>
//void Vector<T>::sort(int lo, int hi) {
//    switch (rand() % 2) {
//        case 0:
//            bubbleSort(lo, hi);
//            break;
//        case 1:
//            selectionSort(lo, hi);
//            break;
//        case 2:
//            quickSort(lo, hi);
//            break;
//        case 3:
//            heapSort(lo, hi);
//            break;
//    }
//}
//
//template<typename T>
//void Vector<T>::sort() {
//    sort(0, _size);
//}
//
//template<typename T>
//void Vector<T>::unsort(int lo, int hi) {
//
//    auto V = _elem + lo;
//    for (int i = hi - lo; i > 0; --i) {
//        std::swap(V[i], V[rand() % i]);
//    }
//}
//
//
//template<typename T>
//int Vector<T>::duplicate() {
//
//    int oldSize = _size;
//
//    for(auto i=1;i<_size;){
//        if(find(_elem[i],0,i)<0){
//            i++;
//        }else{
//            remove(i);
//        }
//
//    }
//    return oldSize - _size;
//}
//
//template<typename T>
//int Vector<T>::uniquify() {
//    auto i = 0, j = 0;
//    while (++j < _size) {
//        if (_elem[i] != _elem[j]) {
//            _elem[++i] = _elem[j];
//        }
//    }
//    _size = ++i;
//    shrink();
//    return j - i;
//}
//
//
////template<typename T>
////void Vector<T>::traverse(void (*visit)(T &)) {
////
////    for (auto i = 0; i < _size; ++i) {
////        visit(_elem[i]);
////    }
////
////}
////
////template<typename T>
////template<typename VST>
////void Vector<T>::traverse(VST const &visit) {
////    for (auto i = 0; i < _size; ++i) {
////        visit(_elem[i]);
////    }
////}
//
//
////template<typename T>
////int Vector<T>::uniquify() {
////    int oldSize = _size;
////    for (auto i = 1; i < _size; ++i) {
////        _elem[i - 1] == _elem[i] ? remove(i) : i++;
////    }
////    return oldSize - _size;
////}
//
//
////template<typename T>
////int Vector<T>::uniquify() {
////    auto i = 0, j = 0;
////    while (++j < _size) {
////        if (_elem[i] != _elem[j]) {
////            _elem[++i] = _elem[j];
////        }
////    }
////    _size = ++i;
////    shrink();
////    return j - i;
////}
//
//
//
////template<typename T>
////int Vector<T>::disordered() const {
////    int n = 0;
////    for (int i = 1; i < _size; ++i) {
////        n += (_elem[i - 1] < _elem[i]);
////    }
////    return n;
////}
//
//
//
//
//template<typename T>
//
//static int binSearch(T *A, T const &e, int lo, int hi) {
//    int mi = (lo + hi) >> 1;
//    if (A[mi] < e) {
//        lo = mi + 1;
//    } else if (e < A[mi]) {
//        hi = mi;
//    } else {
//        return mi;
//    }
//    return -1;
//}
//
//
//// 版本C
//template<typename T>
//int Vector<T>::binSearch(T *S, const T &e, int lo, int hi) {
//    while (lo < hi) {
//        auto mi = (lo + hi) >> 1;
//
//        (e < S[mi]) ? hi = mi : lo = mi + 1;
//        std::cout << lo << " " << hi;
////        S[mi] < e ? hi = mi : lo = mi + 1;
//    }
//    return --lo;
//}
//
//
//
//
//// 版本A
////template<typename T>
////int Vector<T>::binSearch(T *S, const T &e, int lo, int hi) {
////    while (lo < hi) {
////        int mi = (lo + hi) >> 1;
////        if (e < S[mi]) hi = mi;
////        else if (S[mi] < e) lo = mi + 1;
////        else return mi;
////    }
////    return -1;
////}
//
//template<typename T>
//int Vector<T>::fibSearch(T *S, const T &e, int lo, int hi) {
//    for (Fib fib(hi - lo); lo < hi;) {
//        while ((hi - lo) < fib.get()) { fib.prev(); };
//        int mi = fib.get() + lo - 1;
//        if (e < S[mi]) {
//            hi = mi;
//        } else if (S[mi] < e) {
//            lo = mi + 1;
//        } else {
//            return mi;
//        }
//    }
//    return -1;
//}
//
//
//// 版本B
////template<typename T>
////int Vector<T>::binSearch(T *S, const T &e, int lo, int hi) {
////    while (lo + 1 < hi) {
////        int mi = (lo + hi) >> 1;
////        e < S[mi] ? hi = mi : lo = mi;
////    }
////    return e == S[lo] ? lo : -1;
////}
//
//// 版本C
//template<typename T>
//int Vector<T>::binSearch(T *S, const T &e, int lo, int hi) {
//
//    while (lo < hi) {
//        int mi = (lo + hi) >> 1;
//        e < S[mi] ? hi = mi : lo = mi + 1;
//    }
//    return lo - 1;
//}
//
//
//// 插值查找
//template<typename T>
//int Vector<T>::interpolationSearch(T *S, const T &e, int lo, int hi) {
//
//    if (S[hi] == S[lo]) return binSearch(S, e, lo, hi);
//    while (lo < hi) {
//        int mi = lo + (hi - lo) * (e - S[lo]) / (S[hi] - S[lo]);
//        e < S[mi] ? hi = mi : lo = mi + 1;
//    }
//    return lo - 1;
//}
//
//template<typename T>
//void Vector<T>::quickSort(int lo, int hi) {
//
//}
//
//template<typename T>
//void Vector<T>::heapSort(int lo, int hi) {
//
//}
//
//template<typename T>
//int Vector<T>::partition(int lo, int hi) {
//    return 0;
//}
//
//////  普通版本
////template<typename T>
////void Vector<T>::bubbleSort(int lo, int hi) {
////    while (lo < --hi) {
////        for (int i = lo; i < hi; ++i) {
////            if (_elem[i] > _elem[i + 1]) {
////                std::swap(_elem[i], _elem[i + 1]);
////            }
////        }
////    }
////}
//////  提前终止版本
////template<typename T>
////void Vector<T>::bubbleSort(int lo, int hi) {
////    for (bool sorted = false; sorted;) {
////        for (int i = lo; i < --hi; ++i) {
////            if (_elem[i] > _elem[i + 1]) {
////                std::swap(_elem[i], _elem[i + 1]);
////                sorted = ue;
////            }
////        }
////    }
////}
//
//template
//class Vector<int>;
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
