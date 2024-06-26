#if !defined(UNIT_H)
#define UNIT_H

#include <geometry.h>
#include <stdbool.h>

typedef struct {
    Vector position;
    Vector velocity;
    Vector acceleration;
} Unit;

#endif // UNIT_H