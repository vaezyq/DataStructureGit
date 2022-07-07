//
// Created by 22126 on 2022/6/12.
//

#ifndef DATASTRUCTUREGIT_LISTNODE_H
#define DATASTRUCTUREGIT_LISTNODE_H

#define ListNodePoi ListNode<T>*

template<typename T>
class ListNode {
public:
    T data;   //数据域
    ListNodePoi pred; //前驱
    ListNodePoi succ; //后继

    ListNode() = default;;

    explicit ListNode(T e, ListNodePoi p = nullptr, ListNodePoi s = nullptr) : data(e), pred(p), succ(s) {
    }   //默认构造器

    ListNodePoi insertAsPred(T const &e);

      //在此节点前插入节点

    ListNodePoi insertAsSucc(T const &e);
    //在此节点后插入节点

};




#endif //DATASTRUCTUREGIT_LISTNODE_H
