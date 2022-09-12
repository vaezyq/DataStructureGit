//
// Created by 王明龙 on 2022/9/12.
//

#include "Sort.h"

template<typename T>
void Sort<T>::quickSort(int lo, int hi) { //对区间[lo,hi)执行快速排序
    if (hi - lo < 2) return;    //单独元素自然有序
    auto mi = partition_v1(lo, hi - 1);        //对区间[lo,hi]进行轴点构造
    quickSort(lo, mi);         //对mi的前缀递归排序
    quickSort(mi + 1, hi);     //对mi的后缀递归排序
}

template<typename T>
int Sort<T>::partition_v1(int lo, int hi) { //在区间[lo,hi]内构造轴点，并返回其秩
    swap(this->_elem[lo], this->_elem[lo + rand() % (hi - lo + 1)]);   //任选一个元素与首元素交换
    auto pivot = this->_elem[lo];     //取首元素作为轴点
    while (lo < hi) {   //从向量的两端交替的向中间扫描
        while ((lo < hi) && (pivot <= this->_elem[hi])) {   //在不小于pivot的前提下
            hi--; //不断左移
        }
        this->_elem[lo++] = this->_elem[hi];   //将小于pivot的归入左侧序列
        while ((lo < hi) && (this->_elem[lo] <= pivot)) {  //在不大于pivot的前提下
            lo++; //不断右移
        }
        this->_elem[hi--] = this->_elem[lo];  //将大于pivot的归入右侧序列
    }
    this->_elem[lo] = pivot;  //备份的轴点归位
    return lo;
}

template<typename T>
int Sort<T>::partition_v2(int lo, int hi) {
    return 0;
}














