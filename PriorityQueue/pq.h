//
// Created by 王明龙 on 2022/9/9.
//

#ifndef DATASTRUCTUREGIT_PQ_H
#define DATASTRUCTUREGIT_PQ_H

#define  Parent(i)         ( ( ( i ) - 1 ) >> 1 ) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]的左孩子
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]的右孩子
#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子
#define  Bigger(PQ, i, j)  ( PQ[i] >= PQ[j] ? j : i ) //取大者（等时前者优先）
#define  ProperParent(PQ, n, i) /*父子（至多）三者中的大者*/ \
           ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
           ) \
            ) //相等时父节点优先，如此可避免不必要的交换


template<typename T>
void heapify(T *A, int n); //Floyd建堆算法


template<typename T>
struct PQ {    //优先级队列PQ模板类
    virtual void insert(T) = 0;     //按照比较器确定的优先级次序插入词条
    virtual T getMax() = 0;       //取出优先级最高的词条
    virtual T delMax() = 0;       //删除优先级最高的词条
};


template<typename T>
int percolateUp(T *A, int i) {  //上滤
    while (0 < i) {
        auto j = Parent(i);    //考察[i]的父亲j
        if (A[i] >= A[j]) break;
        swap(A[i], A[j]);
        i = j;     //父子换位，并继续考察上一层
    }
    return i;    //返回上滤最终抵达的位置
}

template<typename T>
int percolateDown(T *A, int n, int i) {
    auto j=0;

    while (i!=(j= ProperParent(A,n,i))){  //只要i不是j
        swap(A[i],A[j]);
        i=j; //二者换位，并继续考查下降后的i
    }
    return i;   //返回下滤抵达的位置
}
#endif //DATASTRUCTUREGIT_PQ_H













