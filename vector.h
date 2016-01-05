#ifndef VECTOR_H
#define VECTOR_H

typedef unsigned long Rank;
const Rank START_CAPACITY = 1000;

template <typename T>
class Vector {
public:
    Vector(): _datas(new T[START_CAPACITY]), _size(0), _capacity(START_CAPACITY) { }
    Vector(Rank size): _datas(new T[size * 2 + 1], _size(size), _capacity(size * 2 + 1)) { }

    ~Vector() {
        delete[] _datas;
    }

    inline T& operator [](int idx) {
        return _datas[idx];
    }

    // return vector size
    inline Rank size() const {
        return _size;
    }

    inline bool empty() const {
        return _size == 0;
    }

    // return vector capacity
    inline Rank capacity() const {
        return _capacity;
    }

    // push element at vector end
    inline void push_back(T d) {
        expand();
        _datas[_size++] = d;
    }

    // pop the end element and return it
    inline T pop_back() {
        return _datas[--_size];
    }

    // return the end element
    inline T& back() {
        return _datas[_size - 1];
    }

    // insert an element at some position
    void insert(T d, Rank pos) {
        expand();

        for (Rank i = ++_size; i > pos; i--) {
            _datas[i] = _datas[i - 1];
        }

        _datas[pos] = d;
    }

    // remove the elements in range [lo, hi)
    void remove(int lo, int hi) {
        _size -= (hi - lo);
        for (Rank i = lo; i < _size; i++) {
            _datas[i] = _datas[i + (hi - lo)];
        }
    }

protected:
    T* _datas;
    Rank _size;
    Rank _capacity;

    // expand the vector for hold more elements
    void expand() {
        if (_size < _capacity)
            return;

        T* oldDatas = _datas;
        _datas = new T[_capacity <<= 1];

        for (Rank i = 0; i < _size; ++i) {
            _datas[i] = oldDatas[i];
        }

        delete[] oldDatas;
    }
};

#endif
