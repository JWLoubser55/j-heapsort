#ifndef HSORT_H
#define HSORT_H

#include <stddef.h>

typedef int (*cmp_ptr)(const void *, const void *);

void hsort(void *base, size_t n, size_t size, cmp_ptr compar);

#endif
