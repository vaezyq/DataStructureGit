//
// Created by 22126 on 2022/6/25.
//


#include "List.h"
#include <iostream>

using namespace std;

void visit(int i) {
    cout << i << " ";
}

void Print(List<int> &l) {
    l.traverse(visit);
    cout << endl;
}


template<typename T>
struct Increase {
    virtual void operator()(T &e) const {
        e++;
    }
};

template<typename T>
void increase(List<T> &L) {
    L.traverse(Increase<T>());
}


template
struct Increase<int>;

template<typename T>
struct Half {
    virtual void operator()(T &e) {
        e /= 2;
    }
};


int main() {
//    List<int> l1;
//
//    for (auto i = 0; i < 10; ++i) {
//        l1.insertAsLast(i);
//    }
//    Print(l1);
//
//    List<int> l2(l1);
//    Print(l2);
//
//    List<int> l3(l2, 2, 6);
//    Print(l3);
//
//    List<int> l4(l1.first(), 10);
//
//    Print(l4);
//
//
//    //    访问接口
//    cout << "size of l1: " << l1.size() << endl;
//    // 空
//    cout << "ls is empty? " << boolalpha << l1.isEmpty() << endl;
//
//    cout << "重载[]运算符： " << l1[3] << endl;
//
//
//    cout << "判断是否合法 " << boolalpha << l1.valid(l1.first()) << endl;
//    cout << "判断是否合法 " << boolalpha << l1.valid(l2.first()) << endl;
//
//    cout << "判断是否有序: " << boolalpha << (l1.disordered() == 0) << endl;
//
//
//    l1.reverse();
//    cout << "翻转链表: ";
//    Print(l1);
//    cout << "判断是否有序: " << boolalpha << (l1.disordered() == 0) << endl;
//
//    cout << "无序列表查找：" << l1.find(10)->data << endl;
//
//
//    cout << "最大的元素: " << l1.selectMax()->data << endl;
//
//
//    cout << "可写访问接口测试:" << endl;
//    cout << "首节点插入： " << endl;
//    l1.insertAsFirst(10);
//    Print(l1);
//    cout << "尾节点插入： " << endl;
//    l1.insertAsLast(11);
//    Print(l1);
//
//
//    increase(l1);
//    Print(l1);


    List<int> l1;

    for (auto i = 10; i > 0; --i) {
        l1.insertAsFirst(2 * i + 1);
    }
//    Print(l1);
//    l1[3] = 18;
//    l1.reverse();
//    for (auto i = 5; i > 0; --i) {
//        l1.insertAsFirst(2 * i);
//    }
    Print(l1);
    l1.reverse();
    Print(l1);
//    auto q = l1.first();
//    for (auto i = 0; i < 5; ++i) {
//        q = q->succ;
//    }
//
//    l1.merge(l1.first(), 5, l1, q, 5);
    l1.sort();

    Print(l1);
}










