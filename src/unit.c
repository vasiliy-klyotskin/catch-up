#include <unit.h>
#include <geometry.h>

Unit unit_init(double pos_x, double pos_y) {
    Unit u;
    u.position = vector_init(pos_x, pos_y);
    u.velocity = vector_init(0, 0);
    u.acceleration = vector_init(0, 0);
    return u;
}

void add_return_to_middle_accel(Unit *unit, double coef) {
    unit->acceleration.x += -coef * unit->position.x;
    unit->acceleration.y += -coef * unit->position.y;
}

void add_friction_accel(Unit *unit, double coef) {

}

void add_repulsion_accel(Unit *unit, Unit *neighbor) {

}

void add_run_away_accel(Unit *unit, Unit *catcher) {

}

void set_catch_velocity(Unit *unit, Unit *catchie) {
    
}