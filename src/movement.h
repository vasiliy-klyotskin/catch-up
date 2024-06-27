#if !defined(MOVEMENT_H)
#define MOVEMENT_H

#include <unit.h>

void do_euler_integration_step(Unit *const unit, double delta);
void add_return_to_middle_accel(Unit *unit, double coef);
void add_friction_accel(Unit *unit, double coef);
void add_repulsion_accel(Unit *unit, Unit *neighbor, double coef);
void add_run_away_accel(Unit *unit, Unit *catcher, double coef);
void set_catch_velocity(Unit *unit, Unit *catchie);

#endif // MOVEMENT_H