#if !defined(UNIT_H)
#define UNIT_H

#include <geometry.h>

typedef struct {
    int id;
    Vector position;
    Vector velocity;
    Vector acceleration;
} Unit;

Unit unit_init(const double pos_x, const double pos_y);
Unit *find_nearest(const Unit *const unit, Unit *const others);
void do_euler_integration(Unit *const units, const double delta);
void add_return_to_middle_accel(Unit *const unit, const double coef);
void add_friction_accel(Unit *const unit, const double coef);
void add_repulsion_accel(Unit *const unit, const Unit *const neighbor, const double coef);
void add_run_away_accel(Unit *const unit, const Unit *const catcher, const double coef);
void add_accel(Unit *const unit, const Vector *const accel);
void reset_velocity_when_low(Unit *const unit, const double threshold);
void reset_accel(Unit *const units);
void set_catch_velocity(
    Unit *const unit, 
    const Unit *const catchie,
    const double max_velocity,
    const double velocity_increment_coef,
    const double angle_fitting_coef
);

#endif // UNIT_H