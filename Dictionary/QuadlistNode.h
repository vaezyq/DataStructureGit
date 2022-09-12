//
// Created by 王明龙 on 2022/9/6.
//

#ifndef DATASTRUCTUREGIT_QUADLISTNODE_H
#define DATASTRUCTUREGIT_QUADLISTNODE_H

#define QlistNodePosi QuadlistNode<T>*   //跳转表节点位置

template<typename T>

struct QuadlistNode {  //QuadlistNode模板类
    T entry;   //所存词条
    QlistNodePosi pred;  //前驱节点
    QlistNodePosi succ;  //后继节点
    QlistNodePosi above;  //上邻节点
    QlistNodePosi below;  //下邻节点

    QuadlistNode(T e = T(), QlistNodePosi p = nullptr, QlistNodePosi s = nullptr, QlistNodePosi a = nullptr,
                 QlistNodePosi b = nullptr) : entry(e), pred(p), succ(s), above(a), below(b) {}   //默认构造器

    QlistNodePosi insertAsSuccAbove(T const &e, QlistNodePosi b = nullptr);    //作为当前节点p的后缀、节点b的上邻节点插入

};


#endif //DATASTRUCTUREGIT_QUADLISTNODE_H
