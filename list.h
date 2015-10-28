#ifndef LIST_H
#define LIST_H
#include <cstddef>

template <typename T>
struct ListNode {
    T data;
    ListNode<T>* pred;
    ListNode<T>* succ;

    ListNode() { }
    ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL)
        : data(e), pred(p), succ(s) { }

    ListNode<T>* insertAsPred(const T& e) {
        ListNode<T>* x = new ListNode<T>(e, pred, this);
        pred->succ = x;
        pred = x;
        return x;
    }

    ListNode<T>* insertAsSucc(const T& e) {
        ListNode<T>* x = new ListNode<T>(e, this, succ);
        succ->pred = x;
        succ = x;
        return x;
    }
};

template <typename T>
class List {
protected:
    int _size;
    ListNode<T>* header;
    ListNode<T>* trailer;

    void init() {
        _size = 0;
        header = new ListNode<T>;
        trailer = new ListNode<T>;
        header->pred = trailer->succ = NULL;
        header->succ = trailer;
        trailer->pred = header;
    }

public:
    List() {
        init();
    }

    ~List() {
        clear();
        delete header;
        delete trailer;
    }

    T& operator[] (int r) {
        ListNode<T>* p = first();
        while (r-- > 0)
            p = p->succ;

        return p->data;
    }

    inline int size() {
        return _size;
    }

    inline bool empty() {
        return _size == 0;
    }

    inline ListNode<T>* first() {
        return header->succ;
    }

    inline ListNode<T>* last() {
        return trailer->pred;
    }

    inline ListNode<T>* insertAsFirst(const T& e) {
        ++_size;
        return first()->insertAsPred(e);
    }

    inline ListNode<T>* insertAsLast(const T& e) {
        ++_size;
        return last()->insertAsSucc(e);
    }

    inline ListNode<T>* insertAsPred(ListNode<T>* p, const T& e) {
        ++_size;
        return p->insertAsPred(e);
    }

    inline ListNode<T>* insertAsSucc(ListNode<T>* p, const T& e) {
        ++_size;
        return p->insertAsSucc(e);
    }

    inline T remove(ListNode<T>* p) {
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        T e = p->data;
        delete p;
        --_size;
        return e;
    }

    int clear() {
        int oldSize = _size;

        while (0 < _size) {
            remove(header->succ);
        }

        return oldSize;
    }
};

#endif
