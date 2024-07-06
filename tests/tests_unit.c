#include <macroassert.h>
#include <unit.h>
#include <dynamic_array.h>
#include <stdbool.h>

static void test_init(void) {
    const double x = 5.0;
    const double y = 7.0;

    const Unit u = unit_init(x, y);
    assert_fp_eq(u.acceleration.x, 0);
    assert_fp_eq(u.acceleration.y, 0);
    assert_fp_eq(u.velocity.x, 0);
    assert_fp_eq(u.velocity.y, 0);
    assert_fp_eq(u.position.x, 5.0);
    assert_fp_eq(u.position.y, 7.0);

    const Unit u2 = unit_init(x, y);
    assert_eq(u.id != u2.id, true);
}

static void test_find_nearest_when_others_is_empty(void) {
    const Unit u = unit_init(0, 0);
    Unit *const others = dyn_array_init(Unit);

    const Unit *const nearest = unit_find_nearest(&u, others);

    assert_eq(nearest, NULL);
}

static void test_find_nearest(void) {
    const Unit u = unit_init(0, 0);
    Unit *others = dyn_array_init(Unit);
    dyn_array_push_rval(others, Unit, unit_init(-1, 1));
    dyn_array_push_rval(others, Unit, unit_init(2, 1));
    dyn_array_push_rval(others, Unit, unit_init(0.1, 0.1));
    dyn_array_push_rval(others, Unit, unit_init(12, 4));
    dyn_array_push(others, u);

    const Unit *const nearest = unit_find_nearest(&u, others);

    assert_fp_eq(nearest->position.x, 0.1);
    assert_fp_eq(nearest->position.y, 0.1);
}

void tests_unit(void) {
    test_init();
    test_find_nearest_when_others_is_empty();
    test_find_nearest();
}