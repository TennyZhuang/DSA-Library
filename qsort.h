#ifndef QSORT_H
#define QSORT_H

template <typename T>
inline void swap(T &a, T &b) {
    T t = b;
    b = a;
    a = t;
}

template <typename T>
void qsort(T *A, int lo, int hi) {
    if (lo >= hi)
        return;

    int m = lo;
    for (int i = lo + 1; i <= hi; i++)
        if (A[i] < A[lo])
            swap<T>(A[++m], A[i]);

    swap(A[lo], A[m]);

    qsort(A, lo, m - 1);
    qsort(A, m + 1, hi);
}

#endif