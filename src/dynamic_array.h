#if !defined(DYNAMIC_ARRAY_H)
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 6
#define RESIZE_FACTOR 2

void *_dyn_array_init(const size_t capacity, const size_t stride);
void *_dyn_array_push(void *array, const void *const element);
void dyn_array_pop(void *const array, void *const target);
void dyn_array_remove_last(void *const array);
void dyn_array_free(const void *const array);
void dyn_array_clear(void *const array);
size_t dyn_array_get_length(const void *const array);

#define dyn_array_init(type) _dyn_array_init(INITIAL_CAPACITY, sizeof(type))
#define dyn_array_push(array, element) array = _dyn_array_push(array, &element)
#define dyn_array_push_rval(array, type, element) \
    do { \
        type temp = (element); \
        array = _dyn_array_push(array, &temp); \
    } while (0)

#endif // DYNAMIC_ARRAY_H