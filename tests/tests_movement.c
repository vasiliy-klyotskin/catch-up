#include <macroassert.h>
#include <movement.h>
#include <geometry.h>

void test_euler_integration_step(void) {
    Unit u = unit_init(5, 6);
    u.velocity = vector_init(-2, 3);
    u.acceleration = vector_init(4, -1);

    do_euler_integration_step(&u, 0.1);

    // -2 + 4 * 0.1 = -1.6
    assert_fp_eq(u.velocity.x, -1.6);
    // 3 + -1 * 0.1 = 2.9
    assert_fp_eq(u.velocity.y, 2.9);
    // 5 + -1.6 * 0.1 = 4.84
    assert_fp_eq(u.position.x, 4.84);
    // 6 + 2.9 * 0.1 = 6.29
    assert_fp_eq(u.position.y, 6.29);
}

void test_return_to_middle_when_position_is_zero(void) {
    Unit u = unit_init(0, 0);

    add_return_to_middle_accel(&u, 2);

    assert_fp_eq(u.acceleration.x, 0);
    assert_fp_eq(u.acceleration.y, 0);
}

void test_return_to_middle_when_position_is_not_zero(void) {
    Unit u = unit_init(-2, 3);
    u.acceleration = vector_init(5, 7);

    add_return_to_middle_accel(&u, 2);

    // 5 + -2 * -2 = 9
    assert_fp_eq(u.acceleration.x, 9);
    // 7 + -2 * 3 = 1
    assert_fp_eq(u.acceleration.y, 1);
}

void test_friction_when_velocity_is_zero(void) {
    Unit u = unit_init(0, 0);

    add_friction_accel(&u, 2);

    assert_fp_eq(u.acceleration.x, 0);
    assert_fp_eq(u.acceleration.y, 0);
}

void test_friction_when_velocity_is_not_zero(void) {
    Unit u = unit_init(0, 0);
    u.acceleration = vector_init(5, 7);
    u.velocity = vector_init(-10, 20);

    add_friction_accel(&u, 2);
 
    // 5 + -(-10) * 2 = 25
    assert_fp_eq(u.acceleration.x, 25);
    // 7 + -20 * 2
    assert_fp_eq(u.acceleration.y, -33);
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

void tests_movement(void) {
    test_euler_integration_step();
    test_return_to_middle_when_position_is_zero();
    test_return_to_middle_when_position_is_not_zero();
    test_friction_when_velocity_is_zero();
    test_friction_when_velocity_is_not_zero();
    test_repulsion_if_distance_to_neighbor_is_zero();
    test_repulsion();
    test_run_away_when_distance_is_zero();
    test_run_away();
}