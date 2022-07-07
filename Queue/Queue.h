//
// Created by 22126 on 2022/6/22.
//

#ifndef DATASTRUCTUREGIT_QUEUE_H
#define DATASTRUCTUREGIT_QUEUE_H


#include "../List/List.h"

template<typename T>
class Queue : public List<T> {
public:
    void enqueue(T const &e);

    T dequeue();

    T front();
};






#endif //DATASTRUCTUREGIT_QUEUE_H
