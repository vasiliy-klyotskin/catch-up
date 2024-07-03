#include <macroassert.h>
#include <unit.h>
#include <dynamic_array.h>
#include <stdbool.h>

void test_init(void) {
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

void test_find_nearest_when_others_is_empty(void) {
    const Unit u = unit_init(0, 0);
    Unit *const others = init_dyn_array(Unit);

    const Unit *const nearest = find_nearest(&u, others);

    assert_eq(nearest, NULL);
}

void test_find_nearest(void) {
    const Unit u = unit_init(0, 0);
    Unit *others = init_dyn_array(Unit);
    push_rval_dyn_array(others, Unit, unit_init(-1, 1));
    push_rval_dyn_array(others, Unit, unit_init(2, 1));
    push_rval_dyn_array(others, Unit, unit_init(0.1, 0.1));
    push_rval_dyn_array(others, Unit, unit_init(12, 4));
    push_dyn_array(others, u);

    const Unit *const nearest = find_nearest(&u, others);

    assert_fp_eq(nearest->position.x, 0.1);
    assert_fp_eq(nearest->position.y, 0.1);
}

void test_euler_integration(void) {
    Unit u1 = unit_init(5, 6);
    u1.velocity = vector_init(-2, 3);
    u1.acceleration = vector_init(4, -1);

    Unit u2 = unit_init(7, 2);
    u2.velocity = vector_init(-4, 1);
    u2.acceleration = vector_init(-2, -4);

    Unit *array = init_dyn_array(Unit);
    push_dyn_array(array, u1);
    push_dyn_array(array, u2);

    do_euler_integration(array, 0.1);

    const Unit r_u1 = array[0];
    assert_fp_eq(r_u1.velocity.x, -1.6);
    assert_fp_eq(r_u1.velocity.y, 2.9);
    assert_fp_eq(r_u1.position.x, 4.84);
    assert_fp_eq(r_u1.position.y, 6.29);

    const Unit r_u2 = array[1];
    assert_fp_eq(r_u2.velocity.x, -4.2);
    assert_fp_eq(r_u2.velocity.y, 0.6);
    assert_fp_eq(r_u2.position.x, 6.58);
    assert_fp_eq(r_u2.position.y, 2.06);
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

    assert_fp_eq(u.acceleration.x, 9);
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
 
    assert_fp_eq(u.acceleration.x, 25);
    assert_fp_eq(u.acceleration.y, -33);
}

void test_repulsion_if_distance_to_neighbor_is_zero(void) {
    Unit u = unit_init(0, 0);
    const Unit neighbor = unit_init(0, 0);

    add_repulsion_accel(&u, &neighbor, 2);

    assert_fp_eq(u.acceleration.x, 0);
    assert_fp_eq(u.acceleration.y, 0);
}

void test_repulsion(void) {
    Unit u = unit_init(-1, -1);
    const Unit neighbor = unit_init(2, 3);
    u.acceleration = vector_init(-3, -3);

    add_repulsion_accel(&u, &neighbor, 2);

    assert_fp_eq(u.acceleration.x, -3.5366563146);
    assert_fp_eq(u.acceleration.y, -3.7155417528);
}

void test_run_away_when_distance_is_zero(void) {
    Unit u = unit_init(0, 0);
    const Unit catcher = unit_init(0, 0);

    add_run_away_accel(&u, &catcher, 2);

    assert_fp_eq(u.acceleration.x, 0);
    assert_fp_eq(u.acceleration.y, 0);
}

void test_run_away(void) {
    Unit u = unit_init(-1, -1);
    const Unit catcher = unit_init(2, 3);
    u.acceleration = vector_init(-3, -3);

    add_run_away_accel(&u, &catcher, 2);

    assert_fp_eq(u.acceleration.x, -3.24);
    assert_fp_eq(u.acceleration.y, -3.32);
}

void test_catch_when_objet_velocity_is_zero(void) {
    Unit u = unit_init(1, 1);
    u.velocity.x = 0;
    u.velocity.y = 0;
    const Unit runner = unit_init(5, 4);
    const double any_max_velocity = 1;
    const double velocity_increment_coef = 0.01;
    const double any_angle_fitting_coef = 0;

    set_catch_velocity(&u, &runner, any_max_velocity, velocity_increment_coef, any_angle_fitting_coef);

    assert_fp_eq(u.velocity.x, 0.008);
    assert_fp_eq(u.velocity.y, 0.006);
}

void test_catch_when_objet_velocity_is_zero_and_max_velocity_is_less_than_increment_coef(void) {
    Unit u = unit_init(1, 1);
    u.velocity.x = 0;
    u.velocity.y = 0;
    const Unit runner = unit_init(5, 4);
    const double any_max_velocity = 1;
    const double velocity_increment_coef = 1.01;
    const double any_angle_fitting_coef = 0;

    set_catch_velocity(&u, &runner, any_max_velocity, velocity_increment_coef, any_angle_fitting_coef);

    assert_fp_eq(u.velocity.x, 0.8);
    assert_fp_eq(u.velocity.y, 0.6);
}

void test_catch_when_object_velocity_is_not_collinear_to_displacement_and_velocity_is_not_max_yet(void) {
    Unit u = unit_init(0, 1);
    u.velocity.x = 1;
    u.velocity.y = 0;
    const Unit runner = unit_init(0, 0);
    const double max_velocity = 10;
    const double velocity_increment_coef = 0.5;
    const double angle_fitting_coef = 0.5;

    set_catch_velocity(&u, &runner, max_velocity, velocity_increment_coef, angle_fitting_coef);

    assert_fp_eq(u.velocity.x, 1.06066);
    assert_fp_eq(u.velocity.y, -1.06066);
}

void test_catch_velocity_should_be_equal_max_velocity_when_increment_exceeds_max_velocity(void) {
    Unit u = unit_init(0, 1);
    u.velocity.x = 0.9;
    u.velocity.y = 0;
    const Unit runner = unit_init(0, 0);
    const double max_velocity = 1;
    const double velocity_increment_coef = 0.1001;
    const double angle_fitting_coef = 0.5;

    set_catch_velocity(&u, &runner, max_velocity, velocity_increment_coef, angle_fitting_coef);

    assert_fp_eq(u.velocity.x, 0.707106);
    assert_fp_eq(u.velocity.y, -0.707106);

    u.velocity.x = -0.9;
    u.velocity.y = 0;

    set_catch_velocity(&u, &runner, max_velocity, velocity_increment_coef, angle_fitting_coef);

    assert_fp_eq(u.velocity.x, -0.707106);
    assert_fp_eq(u.velocity.y, -0.707106);
}

void test_reset_velocity(void) {
    Unit u = unit_init(0, 0);
    const double threshold = 1;

    u.velocity.x = 0.6001;
    u.velocity.y = 0.8;

    reset_velocity_when_low(&u, threshold);

    assert_fp_eq(u.velocity.x, 0.6001);
    assert_fp_eq(u.velocity.y, 0.8);

    u.velocity.x = 0.5999;
    u.velocity.y = 0.8;

    reset_velocity_when_low(&u, threshold);

    assert_eq(u.velocity.x, 0);
    assert_eq(u.velocity.y, 0);
}

void tests_unit(void) {
    test_init();
    test_find_nearest_when_others_is_empty();
    test_find_nearest();
    test_euler_integration();
    test_return_to_middle_when_position_is_zero();
    test_return_to_middle_when_position_is_not_zero();
    test_friction_when_velocity_is_zero();
    test_friction_when_velocity_is_not_zero();
    test_repulsion_if_distance_to_neighbor_is_zero();
    test_repulsion();
    test_run_away_when_distance_is_zero();
    test_run_away();
    test_catch_when_objet_velocity_is_zero();
    test_catch_when_objet_velocity_is_zero_and_max_velocity_is_less_than_increment_coef();
    test_catch_when_object_velocity_is_not_collinear_to_displacement_and_velocity_is_not_max_yet();
    test_catch_velocity_should_be_equal_max_velocity_when_increment_exceeds_max_velocity();
    test_reset_velocity();
}