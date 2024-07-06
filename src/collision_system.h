#if !defined(COLLISION_SYSTEM_H)
#define COLLISION_SYSTEM_H

#include <collision.h>
#include <players.h>
#include <stdbool.h>

typedef struct {
    int catch_count;
    bool catch_is_allowed_now;
    bool catch_did_just_occured;
    bool any_hit_just_occured;
    Players *_players;
    Collision *_collisions;
    double _unit_radius;
    int _ticks_since_last_catch;
    int _min_ticks_before_next_catch;
} CollisionSystem;

CollisionSystem col_sys_init(Players *const players, const double fps, const double radius);
void col_sys_free(const CollisionSystem *const col_sys);
void col_sys_resolve_collisions(CollisionSystem *const col_sys);

#endif // COLLISION_SYSTEM_H
