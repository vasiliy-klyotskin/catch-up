#include <random_accels.h>
#include <dynamic_array.h>
#include <stdbool.h>
#include <time.h>

RandomAccels random_accels_init(RandFnMinus1To1 rand_minus1_1, const int update_delay, const double coef) {
    srand(time(NULL));
    RandomAccels accels;
    accels._rand_minus1_1 = rand_minus1_1;
    accels._elements = dyn_array_init(Vector);
    accels._updates_count_before_update = update_delay;
    accels._updates_count_since_last_update = 0;
    accels._coef = coef;
    return accels;
}

static Vector get_random_accel_vec(const RandomAccels *const accels) {
    double x = accels->_rand_minus1_1() * accels->_coef;
    double y = accels->_rand_minus1_1() * accels->_coef;
    return vector_init(x, y);
}

static void recalculate_accels(RandomAccels *const accels) {
    size_t accels_count = dyn_array_get_length(accels->_elements);
    for (size_t i = 0; i < accels_count; i++) {
        accels->_elements[i] = get_random_accel_vec(accels);
    }
}

void random_accels_update(RandomAccels *const accels) {
    if (accels->_updates_count_since_last_update >= accels->_updates_count_before_update) {
        recalculate_accels(accels);
        accels->_updates_count_since_last_update = 0;
    }
    accels->_updates_count_since_last_update++;
}

void random_accels_add(RandomAccels *const accels) {
    dyn_array_push_rval(accels->_elements, Vector, get_random_accel_vec(accels));
}

const Vector *const random_accels_get(const RandomAccels *const accels, const size_t index) {
    return &accels->_elements[index];
}

size_t random_accels_get_count(const RandomAccels *const accels) {
    return dyn_array_get_length(accels->_elements);
}

void random_accels_free(const RandomAccels *const accels) {
    dyn_array_free(accels->_elements);
}