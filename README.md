# m_arr
Dynamic array implementation. Didn't test it enough

I'm pretty there are cases where it doesn't work for example if you don't use primitive types for the array

# How to use
Just include the header file.
```c
#include "m_arr.h"
```

It works with clang, haven't tested it with other compilers.

It compiles fine with

```bash
clang -ansi -Wall -Wextra -Wshadow -Werror -pedantic -pedantic-errors test.c
```


# Usage
```c
int *arr, *arr1, *arr2, *arr3, a;
unsigned int size, capacity

arr = arr_create(sizeof(int), 10);
arr1 = arr_create(sizeof(int), 20);
arr2 = arr_create(sizeof(int), 30);

/* getting the value */
a = arr[5];
/* or */
a = arr_at(5, arr); /* checks if the index is within bounds */

/* resizing */
arr = arr_resize(35, arr);

/* capacity of the array */
arr = arr_reserve(70, arr);

/* getting the size, and capacity */
size = arr_size(arr);
capacity = arr_capacity(arr);

/* joining two arrays */
arr3 = arr_join(arr1, arr2); /* must be of the same type */

/* appending two arrays */
arr1 = arr_append(arr1, arr2);

/* delete an element (doesn't preserve order, but it's faster) */
arr_fdelete(i, arr);

/* delete an element and preserve order */
arr_delete(i, arr);

/* free an array */
arr_free(arr);
arr_free(arr1);
arr_free(arr2);
arr_free(arr3);
```

