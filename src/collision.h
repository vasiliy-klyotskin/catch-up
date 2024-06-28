#if !defined(COLLISION_H)
#define COLLISION_H

#include <unit.h>
#include <stdlib.h>

typedef struct {
    Unit *u1;
    Unit *u2;
} Collision;

void detect_collisions(
    const Unit *const units,
    const Collision *const collisions,
    const double radius
);

#endif // COLLISION_H