#include <dynamic_array.h>

enum {
    CAPACITY,
    LENGTH,
    STRIDE,
    HEADER_FIELDS
};

void *_init_dyn_array(size_t capacity, size_t stride) {
    const size_t header_size = sizeof(size_t) * HEADER_FIELDS;
    const size_t content_size = capacity * stride;
    size_t *arr = (size_t *) malloc(header_size + content_size);
    if (arr == NULL) {
        exit(1);
    }
    arr[CAPACITY] = capacity;
    arr[LENGTH] = 0;
    arr[STRIDE] = stride;
    return (void *) (arr + HEADER_FIELDS);
}

size_t get_header_field(void *array, size_t field) {
    return ((size_t *)(array) - HEADER_FIELDS)[field];
}

void set_header_field(void *array, size_t field, size_t value) {
    ((size_t *)(array) - HEADER_FIELDS)[field] = value;
}

size_t get_stride(void *array) {
    return get_header_field(array, STRIDE);
}

size_t get_length(void *array) {
    return get_header_field(array, LENGTH);
}

size_t get_capacity(void *array) {
    return get_header_field(array, CAPACITY);
}

void *_push_dyn_array(void *array, void *element) {
    if (get_capacity(array) >= get_length(array)) {
        void *temp = _init_dyn_array(get_capacity(array) * RESIZE_FACTOR, get_stride(array));
        memcpy(temp, array, get_capacity(array) * get_stride(array));
        set_header_field(temp, LENGTH, get_length(array));
        free_dyn_array(array);
        array = temp;
    }
    memcpy(array + get_length(array) * get_stride(array), element, get_stride(array));
    set_header_field(array, LENGTH, get_length(array) + 1);
    return array;
}

void pop_dyn_array(void *array, void *target) {
    if (get_length(array) == 0) return;
    memcpy(target, (size_t *) array + get_length(array) * get_stride(array) ,get_stride(array));
    set_header_field(array, LENGTH, get_length(array) - 1);
}

void remove_last_dyn_array(void *array) {
    if (get_length(array) == 0) return;
    set_header_field(array, LENGTH, get_length(array) - 1);
}

size_t get_length_dyn_array(void *array) {
    return get_length(array);
}

void free_dyn_array(void *array) {

}