#include "stdio.h"

#include "m_arr.h"

int main(void) {
  int *arr, *arr1, *arr2, **m;

  unsigned int i, j;

  arr = arr_create(sizeof(int), 10);


  for (i = 0; i < arr_size(arr); ++i)
    arr[i] = i;


  printf("Original arr\n");
  for (i = 0; i < arr_size(arr); ++i)
    printf("%u, %d\n", i, arr_at(i, arr));

  arr_fdelete(5, arr);

  printf("\narr_fdelete at 5\n");
  for (i = 0; i < arr_size(arr); ++i)
    printf("%u, %d\n", i, arr[i]);

  arr_delete(5, arr);

  printf("\narr_delete at 5\n");
  for (i = 0; i < arr_size(arr); ++i)
    printf("%u, %d\n", i, arr_at(i, arr));

  arr1 = arr_create(sizeof(int), 20);

  for (i = 0; i < arr_size(arr1); ++i)
    arr1[i] = i * 2;

  printf("\narr1\n");
  for (i = 0; i < arr_size(arr1); ++i)
    printf("%u, %d\n", i, arr1[i]);

  arr = arr_append(arr, arr1);

  printf("\nappend arr and arr1\n");
  for (i = 0; i < arr_size(arr); ++i)
    printf("%u, %d\n", i, arr_at(i, arr));

  arr2 = arr_join(arr, arr1);

  printf("\njoin arr and arr1 to create arr2\n");
  for (i = 0; i < arr_size(arr2); ++i)
    printf("%u, %d\n", i, arr2[i]);

  /* frees arrays */
  arr_free(arr);
  arr_free(arr1);
  arr_free(arr2);

  m = arr_create(sizeof(int*), 10);

  for (i = 0; i < arr_size(m); ++i)
    m[i] = arr_create(sizeof(int), 10);

  for (i = 0; i < arr_size(m); ++i)
    for (j = 0; j < arr_size(m[i]); ++j)
      m[i][j] = i * arr_size(m[i]) + j;
  
  printf("\ncreate int matrix\n");
  for (i = 0; i < arr_size(m); ++i) {
    for (j = 0; j < arr_size(m[i]); ++j)
      printf("%d\t", m[i][j]);
    printf("\n");
  }
}
