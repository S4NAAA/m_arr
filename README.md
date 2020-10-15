# m_arr
Dynamic array implementation. Didn't test it enough

I'm pretty there are cases where it doesn't work for example if you don't use primitive types for the array
# Usage
```c
int *arr, a;

arr = arr_create(sizeof(int), 10);

/* getting the value */
a = arr[5];
/* or */
a = arr_at(5, arr); /* checks if the index is within bounds */

/* resizing */
arr = arr_resize(35, arr);

/* capacity of the array */
arr = arr_reserve(70, arr);

/* getting the size */
arr_size(arr);
```

