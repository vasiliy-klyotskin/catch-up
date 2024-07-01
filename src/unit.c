#include <unit.h>
#include <dynamic_array.h>
#include <math.h>

Unit unit_init(double pos_x, double pos_y) {
    static int id = 0;
    Unit u;
    u.id = id++;
    u.position = vector_init(pos_x, pos_y);
    u.velocity = vector_init(0, 0);
    u.acceleration = vector_init(0, 0);
    return u;
}

Unit *find_nearest(Unit *const unit, Unit *const others) {
    size_t others_length = get_length_dyn_array(others);
    Unit *nearest = NULL;
    double distance_to_nearest = INFINITY;
    for (size_t i = 0; i < others_length; i++) {
        Unit *other = &others[i];
        Vector displacement = vector_difference(&unit->position, &other->position);
        double distance = vector_magnitude(&displacement);
        if (distance < distance_to_nearest) {
            nearest = other;
            distance_to_nearest = distance;
        }
    }
    return nearest;
}