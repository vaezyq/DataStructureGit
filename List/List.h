//
// Created by 22126 on 2022/6/12.
//

#ifndef DATASTRUCTUREGIT_LIST_H
#define DATASTRUCTUREGIT_LIST_H

#include "ListNode.h"


template<typename T>
class List {
private:
    int _size;     //规模
    ListNodePoi header;   //头哨兵
    ListNodePoi trailer; // 尾哨兵

protected:
    void init(); //列表创建时的初始化,构造函数都可以通过调用这个来简便初始化

    int clear();  //清除所有节点

    void copyNodes(ListNodePoi p, int n);  //复制列表中从p开始的n项

    void insertionSort(ListNodePoi p, int n);

    void selectionSort(ListNodePoi p, int n);

    void mergeSort(ListNodePoi p, int n);

    void merge(ListNodePoi p, int n, List<T> &L, ListNodePoi q, int m);

public:

//构造函数
    List() { init(); };       //默认构造函数

    List(List<T> &L);  //整体复制列表L

    List(List<T> const &L, int r, int n);   //区间复制列表L

    List(ListNodePoi p, int n);  //区间复制列表

//    析构函数
    ~List();

// 只读访问接口

    int size() const; //规模

    bool isEmpty() const; //判空

    T &operator[](int r) const; //重载，支持循秩访问

    ListNodePoi first() const; //首节点位置

    ListNodePoi last() const;  //尾节点位置

    bool valid(ListNodePoi p); //判断位置p是否对外合法

    int disordered();//判断列表是否已经有序

    ListNodePoi find(T const &e);  //无序列表查找

    ListNodePoi find(T const &e, int n, ListNodePoi p);  //无序列表区间查找

    ListNodePoi search(T const &e);  //有序列表查找

    ListNodePoi search(T const &e, int n, ListNodePoi p); //有序列表区间查找

    ListNodePoi selectMax(ListNodePoi p, int n);  //在p及其n-1个后缀中选出最大者

    ListNodePoi selectMax();     //在整体列表中选出最大者

//可写访问接口

    ListNodePoi insertAsFirst(T const &e);  //将e作为首节点插入

    ListNodePoi insertAsLast(T const &e);      //将e作为末节点插入

    ListNodePoi insertA(ListNodePoi p, T const &e);    //将e作为p的后继插入

    ListNodePoi insertB(ListNodePoi p, T const &e); //将e作为p的前驱插入

    T remove(ListNodePoi p); //删除p处的节点

    void merge(List<T> &L); //全列表合并

    void sort(ListNodePoi p, int n); //列表区间排序

    void sort();// 列表整体排序

    int deduplicate();  //无序去重

    int uniquify(); //有序去重

    void reverse(); //前后倒置

    void traverse(void (*visit)(T &t)) {
        auto p = header;
        for (auto i = 0; i < _size; ++i) {
            visit((p = p->succ)->data);
        }
    }
    //指针遍历

    template<typename VST>
    void traverse(VST const&visit) {
        auto p = header;
        for (auto i = 0; i < _size; ++i) {
            visit((p = p->succ)->data);
        }
    }
    //函数对象遍历
};


#endif //DATASTRUCTUREGIT_LIST_H
