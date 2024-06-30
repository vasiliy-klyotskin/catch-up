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

double min(double a, double b) {
    return (a < b) ? a : b;
}

void set_catch_velocity(
    Unit *const unit, 
    const Unit *const catchie,
    const double max_velocity,
    const double velocity_increment_coef,
    const double angle_fitting_coef
) {
    Vector disposition = vector_difference(unit, catchie);
    if (unit->velocity.x == 0 && unit->velocity.y == 0) {
        NormalizedVector norm_disposition = vector_normalized(&disposition);
        const double multiplier = min(velocity_increment_coef, max_velocity);
        unit->velocity.x = norm_disposition.direction.x * multiplier;
        unit->velocity.y = norm_disposition.direction.y * multiplier;
    } else {
        NormalizedVector norm_velocity = vector_normalized(&unit->velocity);
        double potential_vx = unit->velocity.x + velocity_increment_coef * norm_velocity.direction.x;
        double max_vx = max_velocity * norm_velocity.direction.x;
        double potential_vy = unit->velocity.y + velocity_increment_coef * norm_velocity.direction.y;
        double max_vy = max_velocity * norm_velocity.direction.y;
        unit->velocity.x = min(max_vx, potential_vx);
        unit->velocity.y = min(max_vy, potential_vy);
        double radians = vector_radian(&unit->velocity, &disposition);
        double fit_angle = radians * angle_fitting_coef;
        unit->velocity = vector_rotated(&unit->velocity, fit_angle);
    }
}