#if !defined(DYNAMIC_ARRAY_H)
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 6
#define RESIZE_FACTOR 2

void *_init_dyn_array(const size_t capacity, const size_t stride);
void *_push_dyn_array(void *array, const void *const element);
void pop_dyn_array(void *const array, void *const target);
void remove_last_dyn_array(void *const array);
void free_dyn_array(const void *const array);
void clear_dyn_array(void *const array);
size_t get_length_dyn_array(const void *const array);

#define init_dyn_array(type) _init_dyn_array(INITIAL_CAPACITY, sizeof(type))
#define push_dyn_array(array, element) array = _push_dyn_array(array, &element)
#define push_rval_dyn_array(array, type, element) \
    do { \
        type temp = (element); \
        array = _push_dyn_array(array, &temp); \
    } while (0)

#endif // DYNAMIC_ARRAY_H