#include <unit.h>
#include <math.h>
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
    unit->acceleration.x += -coef * unit->velocity.x;
    unit->acceleration.y += -coef * unit->velocity.y;
}

void add_repulsion_accel(Unit *unit, Unit *neighbor, double coef) {
    Vector position_difference = vector_difference(&unit->position, &neighbor->position);
    double distance = vector_magnitude(&position_difference);
    double dependence = -coef / (distance * sqrt(distance));
    unit->acceleration.x += position_difference.x * dependence;
    unit->acceleration.y += position_difference.y * dependence;
}

void add_run_away_accel(Unit *unit, Unit *catcher) {

}

void set_catch_velocity(Unit *unit, Unit *catchie) {
    
}