#if !defined(UNIT_H)
#define UNIT_H

#include <geometry.h>

typedef struct {
    Vector position;
    Vector velocity;
    Vector acceleration;
} Unit;

Unit unit_init(double pos_x, double pos_y);

#endif // UNIT_H