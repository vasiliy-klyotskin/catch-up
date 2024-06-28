#include <movement.h>
#include <math.h>

void do_euler_integration_step(Unit *const unit, const double delta) {
    unit->velocity.x += unit->acceleration.x * delta;
    unit->velocity.y += unit->acceleration.y * delta;
    unit->position.x += unit->velocity.x * delta;
    unit->position.y += unit->velocity.y * delta;
}

void add_return_to_middle_accel(Unit *const unit, const double coef) {
    unit->acceleration.x += -coef * unit->position.x;
    unit->acceleration.y += -coef * unit->position.y;
}

void add_friction_accel(Unit *const unit, const double coef) {
    unit->acceleration.x += -coef * unit->velocity.x;
    unit->acceleration.y += -coef * unit->velocity.y;
}

void add_repulsion_accel(Unit *const unit, const Unit *const neighbor, double coef) {
    const Vector position_difference = vector_difference(&unit->position, &neighbor->position);
    const double distance = vector_magnitude(&position_difference);
    const double dependence = -coef / (distance * sqrt(distance));
    unit->acceleration.x += position_difference.x * dependence;
    unit->acceleration.y += position_difference.y * dependence;
}

void add_run_away_accel(Unit *const unit, const Unit *const catcher, const double coef) {
    const Vector position_difference = vector_difference(&unit->position, &catcher->position);
    const double distance = vector_magnitude(&position_difference);
    const double dependence = -coef / (distance * distance);
    unit->acceleration.x += position_difference.x * dependence;
    unit->acceleration.y += position_difference.y * dependence;
}

void set_catch_velocity(Unit *const unit, const Unit *const catchie) {

}