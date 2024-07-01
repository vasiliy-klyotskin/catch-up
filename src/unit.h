#if !defined(UNIT_H)
#define UNIT_H

#include <geometry.h>

typedef struct {
    Vector position;
    Vector velocity;
    Vector acceleration;
} Unit;

Unit unit_init(double pos_x, double pos_y);
Unit *find_nearest(Unit *const unit, Unit *const others);

#endif // UNIT_H