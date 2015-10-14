#include "vector.h"

template <typename T>
class Stack: public Vector<T> {
public:
    Stack() { }

    inline void push(T d) {
        Vector<T>::push_back(d);
    }

    inline T pop() {
        return Vector<T>::pop_back();
    }

    inline T& top() {
        return Vector<T>::back();
    }
};
