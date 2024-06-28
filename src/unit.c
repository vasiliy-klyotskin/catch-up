#include <unit.h>

Unit unit_init(double pos_x, double pos_y) {
    Unit u;
    u.position = vector_init(pos_x, pos_y);
    u.velocity = vector_init(0, 0);
    u.acceleration = vector_init(0, 0);
    return u;
}