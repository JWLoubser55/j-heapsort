# j-sortlib
Basic *sort implementations
Should build on any system with a C99 compiler

# Using
```c
#define ...SORT_IMPLEMENTATION
...
#include "path/to/...sort.h"
...
/*name*/sort(void *base, size_t n, size_t size, int (*compar)(const void *, const void *));
...
/*name*/sort_r(void *base, size_t n, size_t size, int (*compar)(const void *, const void *, void *), void *arg);
```
