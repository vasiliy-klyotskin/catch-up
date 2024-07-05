#include <macroassert.h>
#include <random_accels.h>

double random_stub(void) {
    static double random_value = 0;
    random_value += 0.1;
    return random_value;
}

void tests_random_accels(void) {
    const int delay = 2;
    const double coef = 2;
    RandomAccels accels = random_accels_init(random_stub, delay, coef);
    assert_eq(random_accels_get_count(&accels), 0);

    random_accels_add(&accels);
    assert_eq(random_accels_get_count(&accels), 1);
    const Vector *const acel_0 = random_accels_get(&accels, 0);
    assert_fp_eq(acel_0->x, 0.2);
    assert_fp_eq(acel_0->y, 0.4);

    random_accels_add(&accels);
    assert_eq(random_accels_get_count(&accels), 2);
    const Vector *const acel_1 = random_accels_get(&accels, 1);
    assert_fp_eq(acel_1->x, 0.6);
    assert_fp_eq(acel_1->y, 0.8);

    random_accels_update(&accels);
    random_accels_update(&accels);
    assert_fp_eq(acel_0->x, 0.2);
    assert_fp_eq(acel_0->y, 0.4);
    assert_fp_eq(acel_1->x, 0.6);
    assert_fp_eq(acel_1->y, 0.8);

    random_accels_update(&accels);
    assert_fp_eq(acel_0->x, 1);
    assert_fp_eq(acel_0->y, 1.2);
    assert_fp_eq(acel_1->x, 1.4);
    assert_fp_eq(acel_1->y, 1.6);
    assert_eq(random_accels_get_count(&accels), 2);

    random_accels_free(&accels);
}