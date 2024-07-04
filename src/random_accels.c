#include <random_accels.h>
#include <dynamic_array.h>
#include <stdbool.h>
#include <time.h>

RandomAccels random_accels_init(RandFnMinus1To1 rand_minus1_1, const int update_delay, const double coef) {
    srand(time(NULL));
    RandomAccels accels;
    accels._rand_minus1_1 = rand_minus1_1;
    accels._elements = init_dyn_array(Vector);
    accels._updates_count_before_reset = update_delay;
    accels._updates_count_since_last_reset = 0;
    accels._coef = coef;
    return accels;
}

static Vector get_random_accel_vec(const RandomAccels *const accels) {
    double x = accels->_rand_minus1_1() * accels->_coef;
    double y = accels->_rand_minus1_1() * accels->_coef;
    return vector_init(x, y);
}

void random_accels_update(RandomAccels *const accels) {
    if (accels->_updates_count_since_last_reset >= accels->_updates_count_before_reset) {
        size_t accels_count = get_length_dyn_array(accels->_elements);
        for (size_t i = 0; i < accels_count; i++) {
            accels->_elements[i] = get_random_accel_vec(accels);
        }
        accels->_updates_count_since_last_reset = 0;
    }
    accels->_updates_count_since_last_reset++;
}

void random_accels_add(RandomAccels *const accels) {
    push_rval_dyn_array(accels->_elements, Vector, get_random_accel_vec(accels));
}

const Vector *const random_accels_get(const RandomAccels *const accels, const size_t index) {
    size_t elements_count = get_length_dyn_array(accels->_elements);
    if (index >= elements_count) return NULL;
    return &accels->_elements[index];
}

void random_accels_free(const RandomAccels *const accels) {
    free_dyn_array(accels->_elements);
}