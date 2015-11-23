#ifndef BINTREE_H
#define BINTREE_H

const int POOL_SIZE = 20000000;

#include "stack.h"
#include "memory_pool.h"

#include <cstddef>

#ifndef NDEBUG
#include <cstdio>
#endif  // NDEBUG

template <typename T>
struct BinNode {
    T data;
    T d1;
    BinNode<T>* parent;
    BinNode<T>* lc;
    BinNode<T>* rc;

    inline BinNode<T>* reset() {
        parent = NULL;
        lc = NULL;
        rc = NULL;
        return this;
    }

    inline BinNode<T>* init(
        T e,
        BinNode<T>* p = NULL,
        BinNode<T>* lc = NULL,
        BinNode<T>* rc = NULL) {
        this->data = e;
        this->lc = lc;
        this->rc = rc;
        return this;
    }

    inline bool isRoot() const {
        return parent == NULL;
    }

    inline bool isLc() const {
        return this == parent->lc;
    }

    inline bool isRc() const {
        return this == parent->rc;
    }

    inline bool hasLc() const {
        return lc != NULL;
    }

    inline bool hasRc() const {
        return rc != NULL;
    }

    inline bool isLeaf() const {
        return !(hasLc() || hasRc());
    }

    inline bool hasBothChildren() const {
        return hasLc() && hasRc();
    }

    inline BinNode<T>* sibling() const {
        return isLc()? parent->rc: parent->lc;
    }

    inline BinNode<T>* uncle() const {
        return parent->sibling();
    }

    // height of subtree
    int size() const {
        return isLeaf()? 1: (lc? lc->size(): 0) + (rc? rc->size(): 0);
    }

    // root's depth is 0
    int depth() const {
        int cnt = 0;

        for (const BinNode<T>* p = this; p; p = p->parent) {
            ++cnt;
        }

        return cnt;
    }
};

template <typename T>
class BinTree {
protected:
    int _size;
    BinNode<T>* _root;
    MemoryPool<BinNode<T>, 1000000> _pool;

    template <typename VST>
    void _visitAlongLeftAndSaveRight(BinNode<T>* x, VST& visit, Stack<BinNode<T>*>& s) {
        while (x) {
            visit(x);
            s.push(x->rc);
            x = x->lc;
        }
    }

    template <typename VST>
    void _travPre(BinNode<T>* x, VST& visit) {
        Stack<BinNode<T>*> s;
        while (true) {
            _visitAlongLeftAndSaveRight(x, visit, s);
            if (s.empty()) {
                break;
            }
            x = s.pop();
        }
    }

public:
    BinTree(): _size(0), _root(NULL) { }

    BinTree(BinNode<T>* r): _root(r), _size(r->size()) { }

    ~BinTree() {
        remove(_root);
    }

    inline int size() const {
        return _size;
    }

    inline bool empty() const {
        return _root == NULL;
    }

    inline BinNode<T>* root() {
        return _root;
    }

    inline BinNode<T>* insertAsRoot(const T& e) {
        _root = _pool.allocate()->init(e);
        _root->data = e;
        _size = 1;
        return _root;
    }

    inline BinNode<T>* insertAsLc(BinNode<T>* p, const T& e) {
        p->lc = _pool.allocate()->init(e, p);
        ++_size;
        return p->lc;
    }

    inline BinNode<T>* insertAsRc(BinNode<T>* p, const T& e) {
        p->rc = _pool.allocate()->init(e, p);
        ++_size;
        return p->rc;
    }

    inline BinNode<T>* attachAsLc(BinNode<T>* p, BinNode<T>* x) {
        if (p->lc)
            remove(p->lc);
        x->parent = p;
        p->lc = x;
        _size += x->size();
    }

    inline BinNode<T>* attachAsRc(BinNode<T>* p, BinNode<T>* x) {
        if (p->rc)
            remove(p->rc);

        x->parent = p;
        p->rc = x;
        _size += x->size();
    }

    int remove(BinNode<T>*& x) {
        if (x == NULL) {
            return 0;
        }

        int num = remove(x->lc) + remove(x->rc) + 1;
        _pool.deallocate(x);
        --_size;
        x = NULL;
        return num;
    }

    enum TraveOrder {
        PRE = 0,
        IN,
        POST
    };

    template <typename VST>
    void traverse(BinNode<T>* x, VST& visit, TraveOrder order = PRE) {
        switch (order) {
        case PRE:
            _travPre<VST> (x, visit);
            break;
        // TODO: travIn and travPost
        }
    }
};

#endif  // BINTREE_H
