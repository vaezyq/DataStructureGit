//
// Created by 22126 on 2022/6/22.
//

#include "Queue.h"

template<typename T>
void Queue<T>::enqueue(const T &e) {
    insertAsLast(e);
}

template<typename T>
T Queue<T>::dequeue() {
    return remove(first());
}

template<typename T>
T Queue<T>::front() {
    return first()->data;
}