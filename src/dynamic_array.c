#include <dynamic_array.h>

enum {
    CAPACITY,
    LENGTH,
    STRIDE,
    HEADER_FIELDS
};

void *_dyn_array_init(const size_t capacity, const size_t stride) {
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

static size_t get_header_field(const void *const array, const size_t field) {
    return ((size_t *)(array) - HEADER_FIELDS)[field];
}

static void set_header_field(void *const array, const size_t field, const size_t value) {
    ((size_t *)(array) - HEADER_FIELDS)[field] = value;
}

void *_dyn_array_push(void *array, const void *const element) {
    const size_t capacity = get_header_field(array, CAPACITY);
    const size_t length = get_header_field(array, LENGTH);
    const size_t stride = get_header_field(array, STRIDE);
    if (capacity <= length) {
        void *temp = _dyn_array_init(capacity * RESIZE_FACTOR, stride);
        memcpy(temp, array, capacity * stride);
        dyn_array_free(array);
        array = temp;
    }
    memcpy((char *)array + length * stride, element, stride);
    set_header_field(array, LENGTH, length + 1);
    return array;
}

void dyn_array_pop(void *const array, void *const target) {
    const size_t length = get_header_field(array, LENGTH);
    const size_t stride = get_header_field(array, STRIDE);
    if (length == 0) { 
        return; 
    }
    memcpy(target, (char *)array + (length -1) * stride, stride);
    set_header_field(array, LENGTH, length - 1);
}

void dyn_array_remove_last(void *const array) {
    const size_t length = get_header_field(array, LENGTH);
    if (length == 0) { 
        return;
    }
    set_header_field(array, LENGTH, length - 1);
}

void dyn_array_clear(void *const array) {
    set_header_field(array, LENGTH, 0);
}

size_t dyn_array_get_length(const void *const array) {
    return get_header_field(array, LENGTH);
}

void dyn_array_free(const void *const array) {
    free((size_t *)array - HEADER_FIELDS);
}