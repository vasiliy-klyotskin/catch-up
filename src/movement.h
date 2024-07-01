#if !defined(MOVEMENT_H)
#define MOVEMENT_H

#include <unit.h>

void do_euler_integration(Unit *const units, const double delta);
void add_return_to_middle_accel(Unit *const unit, const double coef);
void add_friction_accel(Unit *const unit, const double coef);
void add_repulsion_accel(Unit *const unit, const Unit *const neighbor, const double coef);
void add_run_away_accel(Unit *const unit, const Unit *const catcher, const double coef);
void reset_velocity_when_low(Unit *const unit, const double threshold);
void reset_accel(Unit *const unit);
void set_catch_velocity(
    Unit *const unit, 
    const Unit *const catchie,
    const double max_velocity,
    const double velocity_increment_coef,
    const double angle_fitting_coef
);

#endif // MOVEMENT_H