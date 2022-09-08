
#include "Vector.h"
#include "Fib.h"
#include <iostream>

using namespace std;

template<typename T>
void Vector<T>::copyFrom(const T *A, int lo, int hi) {

    _elem = new T[_capacity = (hi - lo) << 1];
    for (_size = 0; lo < hi; _elem[_size++] = A[lo++]);
}

template<typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return; //不需要扩容
    auto oldElem{_elem};
    _capacity = std::max(DEFAULT_CAPACITY, _capacity);
    _elem = new T[_capacity <<= 1];
    for (auto i = 0; i < _size; ++i) {
        _elem[i] = oldElem[i];
    }
    delete[]oldElem;
}

template<typename T>
void Vector<T>::shrink() {
    if (_size > _capacity >> 2) return;  //当存储的元素数目小于总容量的1/4时，需要扩容
    auto oldElem{_elem};
    _elem = new T[_capacity = std::max(_capacity >> 1, DEFAULT_CAPACITY)];
    for (auto i = 0; i < _size; ++i) {
        _elem[i] = oldElem[i];
    }
    delete[]oldElem;
}


template<typename T>
bool Vector<T>::bubble_v1(int lo, int hi) {  //冒泡排序最简单的写法，当[lo,hi)内元素全部有序，则不再需要排序
    auto sorted{true};
    while (lo + 1 < hi) {
        if (_elem[lo] > _elem[lo + 1]) {
            sorted = false;
            std::swap(_elem[lo], _elem[lo + 1]);
        }
        lo++;
    }
    return sorted;
}

template<typename T>
void Vector<T>::bubbleSort_v1(int lo, int hi) {  //调用bubble_v1进行排序，当[lo,hi)已经有序，则停止执行
    auto sorted{true};
    while (!sorted && hi > lo) {
        sorted = bubble_v1(lo, hi--);
    }
}


template<typename T>
int Vector<T>::bubble_v2(int lo, int hi) {
    auto last{lo};
    while (lo + 1 < hi) {
        if (_elem[lo] > _elem[lo + 1]) {
            last = lo;
            std::swap(_elem[lo], _elem[lo + 1]);
        }
        lo++;
    }
    return last;
}

template<typename T>
void Vector<T>::bubbleSort_v2(int lo, int hi) {  //调用bubble_v2进行排序，下一次的排序区间为[lo,last)
    while (lo < (hi = bubble_v2(lo, hi)));
}


template<typename T>
int Vector<T>::bubble_v3(int lo, int hi) {
    auto first{hi};

    while (lo + 1 < hi) {
        if (_elem[hi - 1] < _elem[hi - 2]) {
            std::swap(_elem[hi - 1], _elem[hi - 2]);
            first = hi - 1;
        }
        hi--;
    }
    return first;
}

template<typename T>
void Vector<T>::bubbleSort_v3(int lo, int hi) {  //调用bubble_v3进行排序，下一次的排序区间为[first,hi)
    while ((lo = bubble_v3(lo, hi)) < hi);
}

template<typename T>
void Vector<T>::bubble_v4(int &lo, int &hi) {
    int rein{0};
    auto first{hi}, last{lo};
    while (lo + 1 < hi) {
        if (rein) {
            if (_elem[lo + 1] < _elem[lo]) {
                std::swap(_elem[lo], _elem[lo + 1]);
                last = lo + 1;
            }
            lo++;
            rein = 0;
        } else {
            if (_elem[hi - 1] < _elem[hi - 2]) {
                std::swap(_elem[hi - 1], _elem[hi - 2]);
                first = hi - 1;
            }
            hi--;
            rein = 1;
        }
    }
}

template<typename T>
void Vector<T>::bubbleSort_v4(int lo, int hi) {  //调用bubble_v4进行排序，下一次的排序区间为[last,first)
    while (lo < hi) {
        bubble_v4(lo, hi);
    }
}

template<typename T>
int Vector<T>::max(int lo, int hi) {
    auto maxElem{_elem[hi - 1]};
    for (auto i = hi - 2; i >= lo; --i) {
        if (_elem[i] > maxElem) maxElem = _elem[i];
    }
    return maxElem;
}

template<typename T>
int Vector<T>::maxItem(int lo, int hi) {
    auto maxElem{_elem[hi - 1]};
    auto maxIdx{hi - 1};
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
    while (lo < hi) {
        std::swap(_elem[hi - 1], _elem[maxItem(lo, hi)]);
        hi--;
    }
}


template<typename T>
void Vector<T>::merge(int lo, int mi, int hi) { //合并两个有序子区间[lo,mi)和[mi,hi)
    auto loElem = new T[mi - lo];
    for (auto i = lo; i < mi; ++i) {
        loElem[i - lo] = _elem[i];
    }
    auto i = 0, j = mi, k = lo;
    while ((i < mi - lo) && (j < hi)) {
        _elem[k++] = (loElem[i] > _elem[j] ? _elem[j++] : loElem[i++]);
    }
    while (i < mi - lo) {
        _elem[k++] = loElem[i++];
    }
}

template<typename T>
void Vector<T>::mergeSort(int lo, int hi) {
    if (lo + 1 >= hi) return;

    auto mi = (hi + lo) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template<typename T>
int Vector<T>::partition(int lo, int hi) {    //快速划分算法，构造区间[lo,hi)的轴点，并返回秩
    swap(_elem[lo], _elem[lo + rand() % (hi - lo)]);       //任取一个元素与首元素交换位置
    auto pivot = _elem[lo];     //取首元素作为轴点,且经过上一步的交换，等价于随机选取
    while (lo < hi) {    //从向量的两端交替的向中间扫描
        while ((lo < hi) && (pivot <= _elem[hi])) {      //不断的向左拓展右子向量
            hi--;
        }
        _elem[lo] = _elem[hi]; //将小于pivot的元素归于左子向量
        while ((lo < hi) && (_elem[lo] <= pivot)) {
            lo++;  //不断的向右拓展左子向量
        }
        _elem[hi] = _elem[lo];  //将大于pivot的元素归于右子向量
    }
    _elem[lo] = pivot;   //将备份的轴点归位到其排序后的最终位置
    return lo;  //返回轴点位置
}


template<typename T>
int Vector<T>::partition_v2(int lo, int hi) {  //快速划分算法，构造区间[lo,hi)的轴点，并返回秩
    //此算法可以优化所有(几乎所有)元素均重复的退化情况
    swap(_elem[lo], _elem[lo + rand() % (hi - lo)]);       //任选一个元素与首元素交换，作为轴点
    auto pivot = _elem[lo];         //以首元素为轴点，经过上一步的交换，等价于随机选取
    while (lo < hi) {      //从向量的两端交替的向中间扫描

        while (lo < hi) {
            if (pivot < _elem[hi]) {    //在大于pivot的前提下，不断左移
                hi--;
            } else {
                _elem[lo++] = _elem[hi];  //将不符合条件的归入左端子向量
                break;
            }
        }

        while (lo < hi) {
            if (_elem[lo] < pivot) {    //在小于pivot的前提下，不断右移
                lo++;     //向右拓展左子向量
            } else {
                _elem[hi--] = _elem[lo];  //将不符合条件的归入右端子向量
                break;
            }
        }
    }
    _elem[lo] = pivot;  //将备份的轴点记录与前、后子向量之间
    return lo;  //返回轴点的秩
}


template<typename T>
void Vector<T>::quickSort(int lo, int hi) {
    if (hi - lo < 1) return;    //递归基：单元素区间必然有序
    auto mi = partition(lo, hi);  //在区间[lo,hi-1)内构造轴点
    quickSort(lo, mi);  //对前缀进行递归排序
    quickSort(mi, hi);  //对后缀进行递归排序
}

template<typename T>
void Vector<T>::heapSort(int lo, int hi) {  //后续补充
}

template<typename T>
Vector<T>::Vector(int c, int s, T v) {
    _elem = new T[_capacity = c];
    _size = s;
    for (auto i = 0; i < s; ++i) {
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
        if (_elem[i] < _elem[i - 1]) outOfOrder++;
    }
    return outOfOrder;
}

template<typename T>
int Vector<T>::find(const T &e) const {
    return find(e, 0, _size);
}

template<typename T>
int Vector<T>::find(const T &e, int lo, int hi) const {   //无序向量查找，未查找到返回lo-1
    auto idx = hi - 1;
    while (idx >= lo) {
        if (_elem[idx] == e) break;
        idx--;
    }
    return idx;
}

template<typename T>
int Vector<T>::search(const T &e, int lo, int hi) const {
    switch (rand() % 3) {
        case 0:
        default:

            return binSearch(_elem, e, lo, hi);
            break;
        case 1:
            return fibSearch(_elem, e, lo, hi);
            break;
        case 2:
            return interpolationSearch(_elem, e, lo, hi);
            break;
    }
}

template<typename T>
T &Vector<T>::operator[](int i) {
    return _elem[i];
}

template<typename T>
T Vector<T>::remove(int r) {
    auto data{_elem[r]};
    remove(r, r + 1);
    return data;
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
    return insert(_size, e);
}

template<typename T>
void Vector<T>::sort(int lo, int hi) {
    switch (rand() % 2) {
        case 0:
            selectionSort(lo, hi);
            break;
        case 1:
        default:
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
    auto oldSize = _size;

    for (auto i = 0; i < _size; ++i) {
        auto res = find(_elem[i], i + 1, _size);
        if (res > i) remove(res);
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

    while (true) {
        if (lo >= hi) return --lo;
        if (S[hi - 1] == S[lo]) return binSearch(S, e, lo, hi);  //相等时分母为0，不再可以使用插值查找
        auto mi = static_cast<int>((e - S[lo]) * (hi - 1 - lo) / (S[hi - 1] - S[lo]));
        if (e < S[mi]) {
            hi = mi;
        } else {
            lo = mi + 1;
        }
    }
}



//template
//class Vector<int>;


