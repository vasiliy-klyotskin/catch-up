#if !defined(UNIT_H)
#define UNIT_H

#include <geometry.h>

typedef struct {
    Vector position;
    Vector velocity;
    Vector acceleration;
} Unit;

void add_comeback_to_middle_accel(Unit *unit);
void add_friction_accel(Unit *unit);
void add_repulsion_accel(Unit *unit, Unit *neighbor);
void add_run_away_accel(Unit *unit, Unit *catcher);
void set_catch_velocity(Unit *unit, Unit *catchie);

#endif // UNIT_H