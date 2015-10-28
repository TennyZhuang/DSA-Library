#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

template <typename T>
class Queue: public List<T> {
public:
    inline ListNode<T>* pushBack(const T& e) {
        return List<T>::insertAsLast(e);
    }

    inline T popFront() {
        return List<T>::remove(List<T>::first());
    }

    inline ListNode<T>* pushFront(const T& e) {
        return List<T>::insertAsFirst(e);
    }

    inline T popBack() {
        return List<T>::remove(List<T>::last());
    }

    inline T& front() {
        return List<T>::first()->data;
    }

    inline T& back() {
        return List<T>::last()->data;
    }
};

#endif
