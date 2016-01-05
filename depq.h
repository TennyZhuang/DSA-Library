#ifndef DEPQ_H
#define DEPQ_H

#include "vector.h"
#include <cassert>

template <typename T>
class DEPQ {
private:
    struct Node {
        T data;
        Rank ptr;

        Node() { }
        Node(T e, Rank ptr): data(e), ptr(ptr) { }

        inline bool operator< (const Node& other) const {
            return data < other.data;
        }
    };

    Vector<Node> _maxH;
    Vector<Node> _minH;

    inline static Rank parent(Rank i) {
        return (i - 1) >> 1;
    }

    inline static Rank lc(Rank i) {
        return (i << 1) + 1;
    }

    inline static Rank rc(Rank i) {
        return (i << 1) + 2;
    }

    // flag = true when swapping in max heap
    // flag = false when swapping in min heap
    inline void swap(Rank i, Rank j, bool flag) {
        if (flag) {
            _minH[_maxH[i].ptr].ptr = j;
            _minH[_maxH[j].ptr].ptr = i;
            Node tmp = _maxH[i];
            _maxH[i] = _maxH[j];
            _maxH[j] = tmp;
        } else {
            _maxH[_minH[i].ptr].ptr = j;
            _maxH[_minH[j].ptr].ptr = i;
            Node tmp = _minH[i];
            _minH[i] = _minH[j];
            _minH[j] = tmp;
        }
    }

    Rank percolateUp(Rank i, bool flag) {
        if (flag) {
            while (i > 0) {
                Rank j = parent(i);

                if (_maxH[i] < _maxH[j]) {
                    break;
                }

                swap(i, j, true);
                i = j;
            }
        } else {
            while (i > 0) {
                Rank j = parent(i);

                if (_minH[j] < _minH[i]) {
                    break;
                }

                swap(i, j, false);
                i = j;
            }
        }

        return i;
    }

    void percolateDown(Rank i, bool flag) {
        if (flag) {
            while (true) {
                Rank l = lc(i);
                Rank r = rc(i);

                if (l >= _maxH.size()) {
                    break;
                } else if (r >= _maxH.size()) {
                    if (_maxH[i] < _maxH[l]) {
                        swap(i, l, true);
                    }

                    break;
                } else if (_maxH[l] < _maxH[i] && _maxH[r] < _maxH[i]) {
                    break;
                } else if (_maxH[l] < _maxH[r]) {
                    swap(i, r, true);
                    i = r;
                } else {
                    swap(i, l, true);
                    i = l;
                }
            }
        } else {
            while (true) {
                Rank l = lc(i);
                Rank r = rc(i);

                if (l >= _minH.size()) {
                    break;
                } else if (r >= _minH.size()) {
                    if (_minH[l] < _minH[i]) {
                        swap(i, l, false);
                    }

                    break;
                } else if (_minH[i] < _minH[l] && _minH[i] < _minH[r]) {
                    break;
                } else if (_minH[l] < _minH[r]) {
                    swap(i, l, false);
                    i = l;
                } else {
                    swap(i, r, false);
                    i = r;
                }
            }
        }
    }

public:
    Rank size() const {
        assert(_minH.size() == _maxH.size());
        return _minH.size();
    }

    void insert(T e) {
        assert(_minH.size() == _maxH.size());

        _maxH.push_back(Node(e, _minH.size()));
        _minH.push_back(Node(e, _maxH.size() - 1));

        Rank i;

        i = _maxH.size() - 1;
        percolateUp(i, true);

        i = _minH.size() - 1;
        percolateUp(i, false);
    }

    T removeMax() {
        assert(_minH.size() == _maxH.size());

        T e = _maxH[0].data;

        Rank i = 0;
        Rank j = _maxH[0].ptr;

        swap(i, _maxH.size() - 1, true);
        swap(j, _minH.size() - 1, false);
        _maxH.pop_back();
        _minH.pop_back();

        percolateDown(i, true);

        if (j > 0 && _minH[j] < _minH[parent(j)]) {
            percolateUp(j, false);
        } else {
            percolateDown(j, false);
        }

        return e;
    }

    T removeMin() {
        assert(_minH.size() == _maxH.size());

        T e = _minH[0].data;

        Rank i = 0;
        Rank j = _minH[0].ptr;

        swap(i, _minH.size() - 1, false);
        swap(j, _maxH.size() - 1, true);
        _minH.pop_back();
        _maxH.pop_back();

        percolateDown(i, false);

        if (j > 0 && _maxH[parent(j)] < _maxH[j]) {
            percolateUp(j, true);
        } else {
            percolateDown(j, true);
        }

        return e;
    }
};

#endif // DEPQ_H
