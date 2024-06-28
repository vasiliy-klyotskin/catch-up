#include <macroassert.h>
#include <collision.h>
#include <dynamic_array.h>
#include <stdbool.h>

bool __compare_units(Unit u1, Unit u2) {
    return u1.position.x == u2.position.x &&
    u1.position.y == u2.position.y &&
    u1.velocity.x == u2.velocity.x &&
    u1.velocity.y == u2.velocity.y &&
    u1.acceleration.x == u2.acceleration.x &&
    u1.acceleration.y == u2.acceleration.y;
}

void test_detect_collision_when_units_are_empty(void) {
    Unit *units = init_dyn_array(Unit);
    Collision *collisions = init_dyn_array(Collision);
    double radius = 1;

    detect_collisions(units, collisions, radius);

    assert_eq(get_length_dyn_array(collisions), 0);
}

void test_detect_collision(void) {
    Unit *units = init_dyn_array(Unit);
    push_rval_dyn_array(units, Unit, unit_init(0, 0));
    push_rval_dyn_array(units, Unit, unit_init(3.99, 0));
    push_rval_dyn_array(units, Unit, unit_init(-4, 0));
    push_rval_dyn_array(units, Unit, unit_init(0, 4.01));
    Collision *collisions = init_dyn_array(Collision);
    double radius = 2;

    detect_collisions(units, collisions, radius);

    assert_eq(get_length_dyn_array(collisions), 1);

    bool correct_collision_detected = 
        (__compare_units(*collisions->u1, unit_init(0, 0)) &&
         __compare_units(*collisions->u2, unit_init(3.99, 0))) ||
        (__compare_units(*collisions->u1, unit_init(3.99, 0)) &&
         __compare_units(*collisions->u2, unit_init(0, 0)));
    assert_eq(correct_collision_detected, true);
}

void tests_collision(void) {
    test_detect_collision_when_units_are_empty();
    test_detect_collision();
}