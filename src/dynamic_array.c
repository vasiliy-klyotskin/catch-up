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
    return arr + HEADER_FIELDS;
}

static size_t get_header_field(void *array, size_t field) {
    return ((size_t *)(array) - HEADER_FIELDS)[field];
}

static void set_header_field(void *array, size_t field, size_t value) {
    ((size_t *)(array) - HEADER_FIELDS)[field] = value;
}

void *_push_dyn_array(void *array, void *element) {
    const size_t capacity = get_header_field(array, CAPACITY);
    const size_t length = get_header_field(array, LENGTH);
    const size_t stride = get_header_field(array, STRIDE);
    if (capacity <= length) {
        void *temp = _init_dyn_array(capacity * RESIZE_FACTOR, stride);
        memcpy(temp, array, capacity * stride);
        free_dyn_array(array);
        array = temp;
    }
    memcpy((char *)array + length * stride, element, stride);
    set_header_field(array, LENGTH, length + 1);
    return array;
}

void pop_dyn_array(void *array, void *target) {
    const size_t length = get_header_field(array, LENGTH);
    const size_t stride = get_header_field(array, STRIDE);
    if (length == 0) { 
        return; 
    }
    memcpy(target, (char *)array + (length -1) * stride, stride);
    set_header_field(array, LENGTH, length - 1);
}

void remove_last_dyn_array(void *array) {
    const size_t length = get_header_field(array, LENGTH);
    if (length == 0) { 
        return;
    }
    set_header_field(array, LENGTH, length - 1);
}

void clear_dyn_array(void *array) {
    set_header_field(array, LENGTH, 0);
}

size_t get_length_dyn_array(void *array) {
    return get_header_field(array, LENGTH);
}

void free_dyn_array(void *array) {
    free((size_t *)array - HEADER_FIELDS);
}