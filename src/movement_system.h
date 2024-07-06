#if !defined(MOVEMENT_SYSTEM_H)
#define MOVEMENT_SYSTEM_H

#include <players.h>
#include <random_accels.h>
#include <stdbool.h>

typedef struct {
    Players *_players;
    RandomAccels _random_accels;
    Unit *_unit_to_catch;
    double _integration_delta;
} MovementSystem;

MovementSystem mv_sys_init(
    RandFnMinus1To1 rand,
    Players *const players,
    const double integration_delta
);
void mv_sys_free(const MovementSystem *const mv_sys);
void mv_sys_resolve_movement(MovementSystem *const mv_sys, const bool need_to_catch);

#endif // MOVEMENT_SYSTEM_H