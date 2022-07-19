//
// Created by 22126 on 2022/6/18.
//

#include "Stack.h"


template<typename T>
void Stack<T>::push(const T &e) {
    this->insert(this->size(), e);

}

template<typename T>
T Stack<T>::pop() {
    return this-> remove(this->size() - 1);
}

template<typename T>
T &Stack<T>::top() {
    return (*this)[this->size() - 1];
}
