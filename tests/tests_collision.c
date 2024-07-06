#include <macroassert.h>
#include <collision.h>
#include <dynamic_array.h>
#include <stdbool.h>

static void test_collision_detect_when_units_are_empty(void) {
    Unit *const units = dyn_array_init(Unit);
    Collision *collisions = dyn_array_init(Collision);
    const double radius = 1;

    collision_detect(units, &collisions, radius);

    assert_eq(dyn_array_get_length(collisions), 0);
}

static void test_collision_detect(void) {
    Unit *units = dyn_array_init(Unit);
    dyn_array_push_rval(units, Unit, unit_init(0, 0));
    dyn_array_push_rval(units, Unit, unit_init(3.99, 0));
    dyn_array_push_rval(units, Unit, unit_init(-4, 0));
    dyn_array_push_rval(units, Unit, unit_init(0, 4.01));
    Collision *collisions = dyn_array_init(Collision);
    const double radius = 2;

    collision_detect(units, &collisions, radius);

    assert_eq(dyn_array_get_length(collisions), 1);
    const Collision collision = collisions[0];
    assert_fp_eq(collision.u1->position.x, 0);
    assert_fp_eq(collision.u1->position.y, 0);
    assert_fp_eq(collision.u2->position.x, 3.99);
    assert_fp_eq(collision.u2->position.y, 0);
    assert_fp_eq(collision.offset.direction.x, 1);
    assert_fp_eq(collision.offset.direction.y, 0);
    assert_fp_eq(collision.offset.magnitude, 3.99);
}

static void test_collision_resolve_when_velocity_is_zero(void) {
    Unit u1 = unit_init(0.01, 0);
    Unit u2 = unit_init(1.99, 0);
    const double radius = 1;

    const NormalizedVector offset = (NormalizedVector) { vector_init(1, 0), 1.98 };
    const Collision collision = (Collision) { &u1, &u2, offset };
    Collision *collisions = dyn_array_init(Collision);
    dyn_array_push(collisions, collision);

    collision_resolve(collisions, radius);

    assert_fp_eq(u1.position.x, 0);
    assert_fp_eq(u1.position.y, 0);
    assert_fp_eq(u2.position.x, 2);
    assert_fp_eq(u2.position.y, 0);
}

static void test_collision_resolve(void) {
    Unit u1 = unit_init(-0.8, -0.85);
    u1.velocity.x = 0;
    u1.velocity.y = 1;
    Unit u2 = unit_init(2.8, 1.85);
    u2.velocity.x = 0;
    u2.velocity.y = -1;
    const double radius = 2.5;
    const NormalizedVector offset = (NormalizedVector) { vector_init(0.8, 0.6), 4.5 };
    const Collision collision = (Collision) { &u1, &u2, offset };
    Collision *collisions = dyn_array_init(Collision);
    dyn_array_push(collisions, collision);

    collision_resolve(collisions, radius);

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
    test_collision_detect_when_units_are_empty();
    test_collision_detect();
    test_collision_resolve_when_velocity_is_zero();
    test_collision_resolve();
}