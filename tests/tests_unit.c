#include <macroassert.h>
#include <unit.h>
#include <geometry.h>

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
}

void test_return_to_middle_when_position_is_zero(void) {
    Unit u = unit_init(0, 0);
    u.acceleration = vector_init(5, 5);

    add_return_to_middle_accel(&u, 2);

    assert_fp_eq(u.acceleration.x, 5);
    assert_fp_eq(u.acceleration.y, 5);
}

void test_return_to_middle_when_position_is_not_zero(void) {
    Unit u = unit_init(-2, 3);
    u.acceleration = vector_init(5, 5);

    add_return_to_middle_accel(&u, 2);

    assert_fp_eq(u.acceleration.x, 9);
    assert_fp_eq(u.acceleration.y, -1);
}

void test_friction_when_velocity_is_zero(void) {
    Unit u = unit_init(0, 0);
    u.acceleration = vector_init(5, 5);

    add_friction_accel(&u, 2);

    assert_fp_eq(u.acceleration.x, 5);
    assert_fp_eq(u.acceleration.y, 5);
}

void test_friction_when_velocity_is_not_zero(void) {
    Unit u = unit_init(0, 0);
    u.acceleration = vector_init(5, 5);
    u.velocity = vector_init(-10, 20);

    add_friction_accel(&u, 2);

    // 
    assert_fp_eq(u.acceleration.x, 25);
    assert_fp_eq(u.acceleration.y, -35);
}

void test_repulsion_if_distance_to_neighbor_is_zero(void) {
    Unit u = unit_init(0, 0);
    Unit neighbor = unit_init(0, 0);

    add_repulsion_accel(&u, &neighbor, 2);

    assert_fp_eq(u.acceleration.x, 0);
    assert_fp_eq(u.acceleration.y, 0);
}

void test_repulsion(void) {
    Unit u = unit_init(-1, -1);
    Unit neighbor = unit_init(2, 3);
    u.acceleration = vector_init(-3, -3);

    add_repulsion_accel(&u, &neighbor, 2);

    // (-2 * (2 - -1) / 5 ^ 1.5) + (-3) = -3.5366563146 (where 5 is distance to neighbor)
    assert_fp_eq(u.acceleration.x, -3.5366563146);
    // (-2 * (3 - -1) / 5 ^ 1.5) + (-3) = -3.7155417528 (where 5 is distance to neighbor)
    assert_fp_eq(u.acceleration.y, -3.7155417528);
}

void test_run_away_when_distance_is_zero(void) {
    Unit u = unit_init(0, 0);
    Unit catcher = unit_init(0, 0);

    add_run_away_accel(&u, &catcher, 2);

    assert_fp_eq(u.acceleration.x, 0);
    assert_fp_eq(u.acceleration.y, 0);
}

void test_run_away(void) {
    Unit u = unit_init(-1, -1);
    Unit catcher = unit_init(2, 3);
    u.acceleration = vector_init(-3, -3);

    add_run_away_accel(&u, &catcher, 2);

    // (-2 * (2 - -1) / 5 ^ 2) + (-3) = -3.24 (where 5 is distance to catcher)
    assert_fp_eq(u.acceleration.x, -3.24);
    // (-2 * (3 - -1) / 5 ^ 2) + (-3) = -3.32 (where 5 is distance to catcher)
    assert_fp_eq(u.acceleration.y, -3.32);
}

void tests_unit(void) {
    test_init();
    test_return_to_middle_when_position_is_zero();
    test_return_to_middle_when_position_is_not_zero();
    test_friction_when_velocity_is_zero();
    test_friction_when_velocity_is_not_zero();
    test_repulsion_if_distance_to_neighbor_is_zero();
    test_repulsion();
    test_run_away_when_distance_is_zero();
    test_run_away();
}