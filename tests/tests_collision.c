#include <macroassert.h>
#include <collision.h>
#include <dynamic_array.h>
#include <stdbool.h>

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
    Collision collision = collisions[0];
    assert_fp_eq(collision.u1->position.x, 0);
    assert_fp_eq(collision.u1->position.y, 0);
    assert_fp_eq(collision.u2->position.x, 3.99);
    assert_fp_eq(collision.u2->position.y, 0);
    assert_fp_eq(collision.offset.direction.x, 1);
    assert_fp_eq(collision.offset.direction.y, 0);
    assert_fp_eq(collision.offset.magnitude, 3.99);
}

void test_resolve_collision_when_velocity_is_zero(void) {
    Unit u1 = unit_init(0.01, 0);
    Unit u2 = unit_init(1.99, 0);
    double radius = 1;

    NormalizedVector offset = (NormalizedVector) { vector_init(1, 0), 1.98 };
    Collision collision = (Collision) { &u1, &u2, offset };
    Collision *collisions = init_dyn_array(Collision);
    push_dyn_array(collisions, collision);

    resolve_collisions(collisions, radius);

    assert_fp_eq(u1.position.x, 0);
    assert_fp_eq(u1.position.y, 0);
    assert_fp_eq(u2.position.x, 2);
    assert_fp_eq(u2.position.y, 0);
}

void test_resolve_collisions(void) {
    Unit u1 = unit_init(-0.8, -0.85);
    u1.velocity.x = 0;
    u1.velocity.y = 1;
    Unit u2 = unit_init(2.8, 1.85);
    u2.velocity.x = 0;
    u2.velocity.y = -1;
    double radius = 2.5;
    NormalizedVector offset = (NormalizedVector) { vector_init(0.8, 0.6), 4.5 };
    Collision collision = (Collision) { &u1, &u2, offset };
    Collision *collisions = init_dyn_array(Collision);
    push_dyn_array(collisions, collision);

    resolve_collisions(collisions, radius);

    assert_fp_eq(u1.position.x, -1);
    assert_fp_eq(u1.position.y, -1);
    assert_fp_eq(u2.position.x, 3);
    assert_fp_eq(u2.position.y, 2);
    assert_fp_eq(u1.velocity.x, -0.96);
    assert_fp_eq(u1.velocity.y, 0.28);
    assert_fp_eq(u2.velocity.x, 0.96);
    assert_fp_eq(u2.velocity.y, -0.28);
}

void tests_collision(void) {
    test_detect_collision_when_units_are_empty();
    test_detect_collision();
    test_resolve_collision_when_velocity_is_zero();
    test_resolve_collisions();
}