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

#endif // UNIT_H