//
// Created by 王明龙 on 2022/9/6.
//

#include "Skiplist.h"


template<typename K, typename V>
V *Skiplist<K, V>::get(K k) {          //跳转表词条查找算法
    if (this->isEmpty()) return nullptr;
    auto qlist = this->first();
    auto p = qlist->data->first();   //首节点开始
    return skipSearch(qlist, p, k) ? (p->entry.value) : nullptr;
}

template<typename K, typename V>
bool Skiplist<K, V>::skipSearch(List<Quadlist<Entry<K, V>> *> *&qlist, QuadlistNode<Entry<K, V>> *&p, K &k) {
    while (true) {
        while (p->succ && (p->entry.key <= k)) {     //从前向后查找
            p = p->succ;   //直到entry的key比k要大或p抵达trailer
        }
        p = p->pred;
        if (p->pred && (k == p->entry.key)) return true;     //命中
        qlist = qlist->succ;   //转入下一层
        if (!qlist->succ) return false;   //已经到达尾部
        p = (p->pred) ? p->below : qlist->data->first();    //转移至当前节点的下一节点
    }
}

template<typename K, typename V>
bool Skiplist<K, V>::put(K k, V v) {
    auto e = Entry<K, V>(k, v);
    if(this->isEmpty()){
        this->insertAsFirst( new Quadlist<Entry<K,V>>);      //插入首个Entry创建Quadlist
    }



}
