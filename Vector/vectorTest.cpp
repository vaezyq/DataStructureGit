//
// Created by 22126 on 2022/6/22.
//


#include "Vector.h"
#include <iostream>


using namespace std;

void visit(int i) {
    cout << i << " ";
}

void Print(Vector<int> &v) {
    v.traverse(visit);
    cout << endl << "--------------" << endl;
}


int main() {


    cout << "构造函数测试" << endl;
    Vector<int> v1(10, 5, 2);
    Print(v1);

    int a[]{1, 2, 3, 4, 5};
    Vector<int> v2(a, 3);
    Print(v2);

    Vector<int> v3(a, 2, 5);
    Print(v3);

    Vector<int> v4(v1);
    Print(v4);


    cout << "属性测试" << endl;
    cout << "The size of v1 is " << v1.size() << endl;
    cout << "Whether v1 is empty: " << boolalpha << v1.isEmpty() << endl;
    cout << "v1是否有序" << static_cast<bool>(v1.disordered() == 0) << boolalpha << endl;

    cout << "无序向量查找测试" << endl;

    cout << "search the position of 1 in v1: " << v1.find(1) << endl;

    cout << "search the position of 2 in v1: " << v1.find(2) << endl;

    cout << "search the position of 1 in interval[0,5] of v1: " << v1.find(1, 0, 5) << endl;

    cout << "search the position of 2 in interval[0,5] of v1: " << v1.find(2, 0, 5) << endl;


    cout << "有序向量查找测试" << endl;

    cout << "search the position of 1 in v2: " << v2.search(1) << endl;

    cout << "search the position of 2 in v2: " << v2.search(2) << endl;

    cout << "search the position of 1 in interval[0,5] of v2: " << v2.search(1, 0, 3) << endl;

    cout << "search the position of 2 in interval[0,5] of v2: " << v2.search(2, 0, 3) << endl;


    cout << "可写访问接口测试：" << endl;
    cout << "重载[]运算符测试： " << v2[1] << endl;

    Vector<int> v5 = v2;
    Print(v5);


    cout << "remove 操作测试：" << endl;
    v5.remove(1);
    Print(v5);

    Vector<int> v6(a, 0, 5);
    v6.remove(0, 2);
    Print(v6);

    cout << "insert 操作测试：" << endl;
    v6.insert(0, 1);
    v6.insert(1, 2);
    v6.insert(6);
    Print(v6);

    cout << "排序算法测试：" << endl;
    cout << "区间置乱测试： " << endl;
    v6.unsort();
    Print(v6);
    v6.sort();
    Print(v6);


    cout << "无序去重测试：" << endl;

    v6.unsort();
    Print(v6);
    v6.insert(2);
    v6.insert(3);
    Print(v6);

    v6.duplicate();
    Print(v6);

    cout << "有序向量去重：" << endl;
    v6.insert(2);
    v6.insert(3);
    v6.sort();
    v6.uniquify();
    Print(v6);
}


