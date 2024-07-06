#if !defined(COLLISION_H)
#define COLLISION_H

#include <unit.h>

typedef struct {
    Unit *u1;
    Unit *u2;
    NormalizedVector offset;
} Collision;

void collision_resolve(Collision *const collisions, const double radius);
void collision_detect(
    Unit *const units,
    Collision **const collisions,
    const double radius
);

#endif // COLLISION_H