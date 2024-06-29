#if !defined(MOVEMENT_H)
#define MOVEMENT_H

#include <unit.h>

void do_euler_integration_step(Unit *const unit, const double delta);
void add_return_to_middle_accel(Unit *const unit, const double coef);
void add_friction_accel(Unit *const unit, const double coef);
void add_repulsion_accel(Unit *const unit, const Unit *const neighbor, const double coef);
void add_run_away_accel(Unit *const unit, const Unit *const catcher, const double coef);
void set_catch_velocity(
    Unit *const unit, 
    const Unit *const catchie,
    const double velocity_increment_coef,
    const double angle_fitting_coef
);

#endif // MOVEMENT_H