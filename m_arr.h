#ifndef M_ARRAY_H
#define M_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define arr_header(a) ((struct m_arr_header *)(a)-1)
#define arr_body(h) ((void *)((struct m_arr_header *)(h) + 1))
#define arr_free(a) free(arr_header(a))
#define arr_create(t_s, s) (m_arr_create(t_s, s))

/* You must use the returned ptr */
#define arr_resize(s, a) (m_arr_resize((void *)(a), s)) 
#define arr_reserve(s, a) (m_arr_reserve((void *)(a), s))

#define arr_size(a) (arr_header(a)->size)
#define arr_type_size(a) (arr_header(a)->type_size)
#define arr_capacity(a) (arr_header(a)->capacity)
#define arr_is_valid_index(i, a) (i >= 0 && i < arr_size(a))
#define arr_is_over_capacity(i, a) (i > arr_capacity(a))

/* 
   0 is always a valid index, there are atleast 16 items 
   stored, so no segfault should occur 
 */
#define arr_at(i, a) a[arr_is_valid_index(i, a) ? i : 0]

#define arr_fdelete(i, a)             \
  do {                                \
    assert(arr_is_valid_index(i, a)); \
    a[i] = a[--arr_size(a)];          \
  } while (0)

#define arr_delete(i, a)                                            \
  do {                                                              \
    assert(arr_is_valid_index(i, a));                               \
    --arr_size(a);                                                  \
    memcpy(&a[i], &a[i + 1], (arr_size(a) - i) * arr_type_size(a)); \
  } while (0)

#define arr_join(a1, a2) (m_arr_join((void *)a1, (void *)a2))
#define arr_append(a1, a2) (m_arr_append((void *)a1, (void *)a2))

struct m_arr_header {
  unsigned int type_size;
  unsigned int size;
  unsigned int capacity;
};

void *m_arr_create(unsigned int type_size, unsigned int size) {
  unsigned int capacity;
  struct m_arr_header *data;

  capacity = (size / 16 + 1) * 16;
  data = malloc(sizeof(struct m_arr_header) + type_size * capacity);

  if (data == NULL) return NULL;

  data->capacity = capacity;
  data->type_size = type_size;
  data->size = (size == 0) ? 1 : size;

  return arr_body(data);
}

void *m_arr_resize(void *arr, unsigned int new_size) {
  unsigned int new_capacity;
  struct m_arr_header *data;

  if (arr == NULL) return NULL;

  data = arr_header(arr);

  if (new_size < data->capacity) goto set_size;

  new_capacity = (new_size / 16 + 1) * 16;
  data = realloc(data,
                sizeof(struct m_arr_header) + data->type_size * new_capacity);

  if (data == NULL) return NULL;

  data->capacity = new_capacity;
set_size:
  data->size = new_size;

  return arr_body(data);
}

void *m_arr_reserve(void *arr, unsigned int new_capacity) {
  struct m_arr_header *data;

  if (arr == NULL) return NULL;

  data = arr_header(arr);
  data = realloc(data,
                sizeof(struct m_arr_header) + data->type_size * new_capacity);

  if (data == NULL) return NULL;

  data->capacity = new_capacity;
  if (data->size > data->capacity) data->size = data->capacity;

  return arr_body(data);
}

/* returns a new array */
void *m_arr_join(void *arr1, void *arr2) {
  char *tmp;
  unsigned int s1;
  struct m_arr_header *data1, *data2;

  tmp = NULL;

  if (arr1 == NULL || arr2 == NULL) goto end;

  data1 = arr_header(arr1);
  data2 = arr_header(arr2);

  if (data1->type_size != data2->type_size) goto end;

  tmp = arr_create(data1->type_size, data1->size + data2->size);

  if (tmp == NULL) goto end;

  s1 = arr_type_size(tmp) * arr_size(arr1);
  
  memcpy(tmp, arr1, s1);
  memcpy(tmp + s1, arr2, arr_type_size(tmp) * data2->size);

end:
  return tmp;
}

/* modifies arr1 */
void *m_arr_append(void *arr1, void *arr2) {
  char *tmp;
  unsigned int s;
  struct m_arr_header *data1, *data2;

  tmp = NULL;

  if (arr1 == NULL || arr2 == NULL) goto end;

  data1 = arr_header(arr1);
  data2 = arr_header(arr2);
  s = data1->size;

  if (data1->type_size != data2->type_size) goto end;

  tmp = arr_resize(data1->size + data2->size, arr1);

  if (tmp == NULL) goto end;

  memcpy(tmp + arr_type_size(tmp) * s, arr2, data2->type_size * data2->size);

end:
  return tmp;
}

#ifdef __cplusplus
}
#endif

#endif
