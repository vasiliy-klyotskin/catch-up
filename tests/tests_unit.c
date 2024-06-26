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
    u.acceleration.x = 5;
    u.acceleration.y = 5;

    add_return_to_middle_accel(&u, 2);

    assert_fp_eq(u.acceleration.x, 5);
    assert_fp_eq(u.acceleration.y, 5);
}

void test_return_to_middle_accel_when_position_is_not_zero() {
    Unit u = unit_init(-2, 3);
    u.acceleration.x = 5;
    u.acceleration.y = 5;

    add_return_to_middle_accel(&u, 2);

    assert_fp_eq(u.acceleration.x, 9);
    assert_fp_eq(u.acceleration.y, -1);
}

void test_friction_is_zero_when_velocity_is_zero() {
    Unit u = unit_init(0, 0);
    u.acceleration.x = 5;
    u.acceleration.y = 5;

    add_friction_accel(&u, 2);

    assert_fp_eq(u.acceleration.x, 5);
    assert_fp_eq(u.acceleration.y, 5);
}

void test_friction_is_zero_when_velocity_is_not_zero() {
    Unit u = unit_init(0, 0);
    u.acceleration.x = 5;
    u.acceleration.y = 5;
    u.velocity.x = -10;
    u.velocity.y = 20;

    add_friction_accel(&u, 2);

    assert_fp_eq(u.acceleration.x, 25);
    assert_fp_eq(u.acceleration.y, -35);
}

void tests_unit() {
    test_init();
    test_return_to_middle_accel_when_position_is_zero();
    test_return_to_middle_accel_when_position_is_not_zero();
    test_friction_is_zero_when_velocity_is_zero();
    test_friction_is_zero_when_velocity_is_not_zero();
}