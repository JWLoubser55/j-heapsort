# Heapsort
A basic heapsort implementation
Should build on any system

# Using
```c
#define HSORT_IMPLEMENTATION
...
#include "path/to/hsort.h"
...
void hsort(void *base, size_t n, size_t size, int (*compar)(const void *, const void *));
```
