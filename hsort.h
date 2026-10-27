#ifndef HSORT_H
#define HSORT_H

#include <stddef.h>

typedef int (*cmp_ptr)(const void *, const void *);
typedef int (*cmp_r_ptr)(const void *, const void *, void *);

void hsort(void *base, size_t n, size_t size, cmp_ptr compar);
void hsort_r(void *base, size_t n, size_t size, cmp_r_ptr compar, void *arg);

#ifdef HSORT_IMPLEMENTATION
#include <stdlib.h>
#include <string.h>

static inline void hsort_memswap(void *x, void *y, void *buf, size_t size)
{
    memcpy(buf, x, size);
    memcpy(x, y, size);
    memcpy(y, buf, size);
}

static inline void sift_down(void *base, size_t root, size_t end, size_t size,
                             cmp_ptr compar, void *buf)
{
    while ((2 * (root) + 1) < end) {
        size_t child = (2 * (root) + 1);

        if (child + 1 < end && compar((char *)base + (child)*size,
                                      (char *)base + (child + 1) * size) < 0) {
            child++;
        }

        if (compar((char *)base + (root)*size, (char *)base + (child)*size) <
            0) {
            hsort_memswap((char *)base + (root)*size, (char *)base + (child)*size,
                       buf, size);
            root = child;
        } else {
            return;
        }
    }
}

static inline void sift_down_r(void *base, size_t root, size_t end, size_t size,
                               cmp_r_ptr compar, void *arg, void *buf)
{
    while ((2 * (root) + 1) < end) {
        size_t child = (2 * (root) + 1);

        if (child + 1 < end &&
            compar((char *)base + (child)*size,
                   (char *)base + (child + 1) * size, arg) < 0) {
            child++;
        }

        if (compar((char *)base + (root)*size, (char *)base + (child)*size,
                   arg) < 0) {
            hsort_memswap((char *)base + (root)*size, (char *)base + (child)*size,
                       buf, size);
            root = child;
        } else {
            return;
        }
    }
}

void hsort(void *base, size_t n, size_t size, cmp_ptr compar)
{
    if (!size || n < 2) {
        return;
    }

    void *buf = malloc(size);

    // heapify
    for (size_t start = (((n - 1) - 1) / 2) + 1; start > 0;) {
        start--;
        sift_down(base, start, n, size, compar, buf);
    }

    // heapsort
    for (size_t i = n - 1; i > 0; i--) {
        hsort_memswap(base, (char *)base + (i)*size, buf, size);
        sift_down(base, 0, i, size, compar, buf);
    }

    free(buf);
}

void hsort_r(void *base, size_t n, size_t size, cmp_r_ptr compar, void *arg)
{
    if (!size || n < 2) {
        return;
    }

    void *buf = malloc(size);

    // heapify
    for (size_t start = (((n - 1) - 1) / 2) + 1; start > 0;) {
        start--;
        sift_down_r(base, start, n, size, compar, arg, buf);
    }

    // heapsort
    for (size_t i = n - 1; i > 0; i--) {
        hsort_memswap(base, (char *)base + (i)*size, buf, size);
        sift_down_r(base, 0, i, size, compar, arg, buf);
    }

    free(buf);
}
#endif

#endif
