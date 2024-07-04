#include <unit.h>
#include <dynamic_array.h>
#include <math.h>
#include <stdbool.h>
#include <util.h>

Unit unit_init(const double pos_x, const double pos_y) {
    static int id = 0;
    Unit u;
    u.id = id++;
    u.position = vector_init(pos_x, pos_y);
    u.velocity = vector_init(0, 0);
    u.acceleration = vector_init(0, 0);
    return u;
}

Unit *find_nearest(const Unit *const unit, Unit *const others) {
    const size_t others_length = get_length_dyn_array(others);
    Unit *nearest = NULL;
    double distance_to_nearest = INFINITY;
    for (size_t i = 0; i < others_length; i++) {
        Unit *const other = &others[i];
        if (other->id == unit->id) {
            continue;
        }
        const Vector displacement = vector_difference(&unit->position, &other->position);
        const double distance = vector_magnitude(&displacement);
        if (distance < distance_to_nearest) {
            nearest = other;
            distance_to_nearest = distance;
        }
    }
    return nearest;
}