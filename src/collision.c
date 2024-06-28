#include <collision.h>
#include <dynamic_array.h>
#include <geometry.h>

void detect_collisions(
    const Unit *const units,
    const Collision *collisions,
    const double radius
) {
    size_t units_length = get_length_dyn_array(units);
    for (size_t u1_index = 0; u1_index < units_length; u1_index++) {
        for (size_t u2_index = u1_index; u2_index < units_length; u2_index++) {
            if (u1_index == u2_index) { continue; }
            Unit *u1 = &units[u1_index];
            Unit *u2 = &units[u2_index];
            Vector difference = vector_difference(u1, u2);
            if (vector_magnitude(&difference) < radius * 2) {
                Collision collision;
                collision.u1 = u1;
                collision.u2 = u2;
                push_dyn_array(collisions, collision);
            }
        }
    }
}