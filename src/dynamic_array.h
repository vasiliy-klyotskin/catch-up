#if !defined(DYNAMIC_ARRAY_H)
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

void *_init_dyn_array(size_t stride);
void push_dyn_array(void *array, void *element);
void pop_dyn_array(void *array, void *target);
void free_dyn_array(void *array);
size_t get_length_dyn_array(void *array);

#define init_dyn_array(type) _init_dyn_array(sizeof(type))

#endif // DYNAMIC_ARRAY_H