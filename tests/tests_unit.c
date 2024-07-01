#include <macroassert.h>
#include <unit.h>
#include <dynamic_array.h>
#include <stdbool.h>

void test_init(void) {
    double x = 5.0;
    double y = 7.0;

    Unit u = unit_init(x, y);
    assert_fp_eq(u.acceleration.x, 0);
    assert_fp_eq(u.acceleration.y, 0);
    assert_fp_eq(u.velocity.x, 0);
    assert_fp_eq(u.velocity.y, 0);
    assert_fp_eq(u.position.x, 5.0);
    assert_fp_eq(u.position.y, 7.0);

    Unit u2 = unit_init(x, y);
    assert_eq(u.id != u2.id, true);
}

void test_find_nearest_when_others_is_empty(void) {
    Unit u = unit_init(0, 0);
    Unit *others = init_dyn_array(Unit);

    Unit *nearest = find_nearest(&u, others);

    assert_eq(nearest, NULL);
}

void test_find_nearest(void) {
    Unit u = unit_init(0, 0);
    Unit *others = init_dyn_array(Unit);
    push_rval_dyn_array(others, Unit, unit_init(-1, 1));
    push_rval_dyn_array(others, Unit, unit_init(2, 1));
    push_rval_dyn_array(others, Unit, unit_init(0.1, 0.1));
    push_rval_dyn_array(others, Unit, unit_init(12, 4));
    push_dyn_array(others, u);

    Unit *nearest = find_nearest(&u, others);

    assert_fp_eq(nearest->position.x, 0.1);
    assert_fp_eq(nearest->position.y, 0.1);
}

void tests_unit(void) {
    test_init();
    test_find_nearest_when_others_is_empty();
    test_find_nearest();
}