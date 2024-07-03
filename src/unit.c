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

void do_euler_integration(Unit *const units, const double delta) {
    const size_t units_length = get_length_dyn_array(units);
    for (size_t i = 0; i < units_length; i++) {
        Unit *unit = &units[i];
        unit->velocity.x += unit->acceleration.x * delta;
        unit->velocity.y += unit->acceleration.y * delta;
        unit->position.x += unit->velocity.x * delta;
        unit->position.y += unit->velocity.y * delta;
    }
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

static void set_catch_initial_velocity(
    Unit *const unit,
    const Vector disposition,
    const double max_velocity,
    const double velocity_increment_coef
) {
    const Vector norm_disposition = vector_normalized(&disposition).direction;
    const double multiplier = min(velocity_increment_coef, max_velocity);
    unit->velocity.x = norm_disposition.x * multiplier;
    unit->velocity.y = norm_disposition.y * multiplier;
}

static void fit_current_velocity(
    Unit *const unit,
    Vector disposition,
    const double max_velocity,
    const double velocity_increment_coef,
    const double angle_fitting_coef
) {
    const Vector norm_velocity = vector_normalized(&unit->velocity).direction;
    const double incremented_vx = unit->velocity.x + norm_velocity.x * velocity_increment_coef;
    const double incremented_vy = unit->velocity.y + norm_velocity.y * velocity_increment_coef;
    const Vector incremented_velocity = vector_init(incremented_vx, incremented_vy);
    const double incremented_vel_magnitude = vector_magnitude(&incremented_velocity);
    if (incremented_vel_magnitude > max_velocity) {
        const double max_vx = max_velocity * norm_velocity.x;
        const double max_vy = max_velocity * norm_velocity.y;
        unit->velocity = vector_init(max_vx, max_vy);
    } else {
        const double incremented_vx = unit->velocity.x + velocity_increment_coef * norm_velocity.x;
        const double incremented_vy = unit->velocity.y + velocity_increment_coef * norm_velocity.y;
        unit->velocity = vector_init(incremented_vx, incremented_vy);
    }
    const double radians = vector_radian(&unit->velocity, &disposition);
    const double fit_angle = radians * angle_fitting_coef;
    unit->velocity = vector_rotated(&unit->velocity, fit_angle);
}

void set_catch_velocity(
    Unit *const unit, 
    const Unit *const catchie,
    const double max_velocity,
    const double velocity_increment_coef,
    const double angle_fitting_coef
) {
    const Vector disposition = vector_difference(&unit->position, &catchie->position);
    const bool is_velocity_zero = unit->velocity.x == 0 && unit->velocity.y == 0;
    if (is_velocity_zero) {
        set_catch_initial_velocity(unit, disposition, max_velocity, velocity_increment_coef);
    } else {
        fit_current_velocity(unit, disposition, max_velocity, velocity_increment_coef, angle_fitting_coef);
    }
}

void reset_velocity_when_low(Unit *const unit, const double threshold) {
    if (vector_normalized(&unit->velocity).magnitude < threshold) {
        unit->velocity.x = 0;
        unit->velocity.y = 0;
    }
}

void reset_accel(Unit *const units) {
    const size_t units_length = get_length_dyn_array(units);
    for (size_t i = 0; i < units_length; i++) {
        units[i].acceleration.x = 0;
        units[i].acceleration.y = 0;
    }
}

void add_accel(Unit *const u, const Vector *const v) {
    u->acceleration.x += v->x;
    u->acceleration.y += v->y;
}