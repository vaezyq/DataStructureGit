//
// Created by 王明龙 on 2022/9/6.
//
#include "Quadlist.h"

template<typename T>
void Quadlist<T>::init() {
    header = new QuadlistNode<T>;     //创建头哨兵节点
    trailer = new QuadlistNode<T>;   //创建尾哨兵节点

    header->succ = trailer;
    header->pred = nullptr;     //横向连接哨兵
    trailer->pred = header;
    trailer->succ = nullptr;     //横向连接哨兵
    header->above = trailer->above = nullptr;  //纵向的后继置空
    header->below = trailer->below = nullptr;    //纵向的前驱置空
    _size = 0;     //记录规模
}
