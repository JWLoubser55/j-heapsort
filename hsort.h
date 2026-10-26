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

static inline void hsort_move(void *x, void *y, void *buf, size_t size)
{
    memcpy(buf, x, size);
    memcpy(x, y, size);
    memcpy(y, buf, size);
}

#define parent(x) (((x) - 1) / 2)
#define left(x) (2 * (x) + 1)
#define heap_index(x) ((char *)base + (x) * size)

static inline void sift_down(void *base, size_t root, size_t end, size_t size,
                             cmp_ptr compar, void *buf)
{
    while (left(root) < end) {
        size_t child = left(root);

        if (child + 1 < end &&
            compar(heap_index(child), heap_index(child + 1)) < 0) {
            child++;
        }

        if (compar(heap_index(root), heap_index(child)) < 0) {
            hsort_move(heap_index(root), heap_index(child), buf, size);
            root = child;
        } else {
            return;
        }
    }
}

static inline void sift_down_r(void *base, size_t root, size_t end, size_t size,
                               cmp_r_ptr compar, void *arg, void *buf)
{
    while (left(root) < end) {
        size_t child = left(root);

        if (child + 1 < end &&
            compar(heap_index(child), heap_index(child + 1), arg) < 0) {
            child++;
        }

        if (compar(heap_index(root), heap_index(child), arg) < 0) {
            hsort_move(heap_index(root), heap_index(child), buf, size);
            root = child;
        } else {
            return;
        }
    }
}

void hsort(void *base, size_t n, size_t size, cmp_ptr compar)
{
    if (!size) {
        return;
    }

    void *buf = malloc(size);

    for (size_t start = parent(n - 1) + 1; start > 0;) {
        start--;
        sift_down(base, start, n, size, compar, buf);
    }

    for (size_t i = n - 1; i > 0; i--) {
        hsort_move((char *)base, heap_index(i), buf, size);
        sift_down(base, 0, i, size, compar, buf);
    }

    free(buf);
}

void hsort_r(void *base, size_t n, size_t size, cmp_r_ptr compar, void *arg)
{
    if (!size) {
        return;
    }

    void *buf = malloc(size);

    for (size_t start = parent(n - 1) + 1; start > 0;) {
        start--;
        sift_down_r(base, start, n, size, compar, buf, arg);
    }

    for (size_t i = n - 1; i > 0; i--) {
        hsort_move((char *)base, heap_index(i), buf, size);
        sift_down_r(base, 0, i, size, compar, buf, arg);
    }

    free(buf);
}

#undef parent
#undef left
#undef heap_index
#endif

#endif
