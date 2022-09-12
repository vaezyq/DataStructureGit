//
// Created by 王明龙 on 2022/9/6.
//

#ifndef DATASTRUCTUREGIT_QUADLIST_H
#define DATASTRUCTUREGIT_QUADLIST_H

#include "QuadlistNode.h"   //引入QuadlistNode节点类

template<typename T>
class Quadlist {    //Quadlist模板类
private:
    int _size;  //规模
    QlistNodePosi header;   //头哨兵
    QlistNodePosi trailer;  //尾哨兵

protected:
    void init();  //Quadlist创建时的初始化
    int clear(); //清除所有节点
public:
    Quadlist() { init(); }   //默认构造函数

    ~Quadlist() {   //析构函数：删除所有节点，并释放哨兵
        clear();
        delete header;
        delete trailer;
    }

    int size() const { return _size; } //规模

    bool empty() const { return _size <= 0; }  //判空

    QlistNodePosi first() const {  //首节点位置
        return header->succ;
    }

    QlistNodePosi last() const {  //末节点位置
        return trailer->pred;
    }

    bool valid(QlistNodePosi p) {    //判断位置p对外是否合法
        return p && (trailer != p) && (header != p);
    }


    //可写访问接口

    T remove(QlistNodePosi p);    //删除位置p处节点，返回被删除的节点的数值

    QlistNodePosi insertAfterAbove(T const &e, QlistNodePosi p, QlistNodePosi b = nullptr);     //将数值e作为节点p的后继，b的上邻插入

    //遍历
    void traverse(void (*)(T &));       //遍历各节点，依次实施指定操作

    template<class VST>
    void traverse(VST &);         //遍历各节点，依次实施指定操作


};


#endif //DATASTRUCTUREGIT_QUADLIST_H









