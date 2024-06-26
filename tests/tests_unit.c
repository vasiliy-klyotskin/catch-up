#include <macroassert.h>
#include <unit.h>

void test_init() {
    double x = 5.0;
    double y = 7.0;

    Unit u = unit_init(x, y);

    assert_fp_eq(u.acceleration.x, 0);
    assert_fp_eq(u.acceleration.y, 0);
    assert_fp_eq(u.velocity.x, 0);
    assert_fp_eq(u.velocity.y, 0);
    assert_fp_eq(u.position.x, 5.0);
    assert_fp_eq(u.position.y, 7.0);
}

void test_return_to_middle_accel_when_position_is_zero() {
    Unit u = unit_init(0, 0);

    add_return_to_middle_accel(&u, 3);

    assert_fp_eq(u.acceleration.x, 0);
    assert_fp_eq(u.acceleration.y, 0);
}

void tests_unit() {
    test_init();
    test_return_to_middle_accel_when_position_is_zero();
}