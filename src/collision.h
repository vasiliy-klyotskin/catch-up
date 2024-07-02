#if !defined(COLLISION_H)
#define COLLISION_H

#include <unit.h>
#include <stdlib.h>

typedef struct {
    Unit *u1;
    Unit *u2;
    NormalizedVector offset;
} Collision;

void resolve_collisions(Collision *const collisions, const double radius);
void detect_collisions(
    Unit *const units,
    Collision *collisions,
    const double radius
);

#endif // COLLISION_H