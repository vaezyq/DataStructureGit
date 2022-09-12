//
// Created by 王明龙 on 2022/9/6.
//

#ifndef DATASTRUCTUREGIT_SKIPLIST_H
#define DATASTRUCTUREGIT_SKIPLIST_H

#include "Dictionary.h"
#include "Entry.h"
#include "../List/List.h"
#include "Quadlist.h"

template<typename K, typename V>

class Skiplist : public Dictionary<K, V>, public List<Quadlist<Entry<K, V>> *> {
protected:
//    bool skipSearch()

public:


    //last()为调用的list的last方法，返回存储于列表末尾的Quadlist<Entry<K, V>> *
    //调用Quadlist<Entry<K, V>> 的size函数，返回此Quadlist的规模
    int size() const { return this->isEmpty() ? 0 : this->last()->data->size(); }    //

    int level() { return this->size(); }      //返回跳转表的规模

    bool put(K, V);      //插入(Skiplist允许重复)

    V *get(K k); //读取

    bool remove(K k); //删除

  //从顶层qlist，以及首节点p出发，向右、向下查找目标关键码k
    bool skipSearch(List<Quadlist<Entry<K, V>> *> *&qlist, QuadlistNode<Entry<K, V>> *&p, K &k);

};


#endif //DATASTRUCTUREGIT_SKIPLIST_H
