#include <macroassert.h>
#include <collision.h>
#include <dynamic_array.h>

void test_detect_collision_when_units_are_empty(void) {
    Unit *units = init_dyn_array(Unit);
    Collision *collisions = init_dyn_array(Collision);
    double radius = 1;

    detect_collisions(units, collisions, radius);

    assert_eq(get_length_dyn_array(collisions), 0);
}

void tests_collision(void) {
    test_detect_collision_when_units_are_empty();
}