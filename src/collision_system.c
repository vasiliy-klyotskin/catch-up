#include <collision_system.h>
#include <dynamic_array.h>

#define MIN_SECONDS_BEFORE_NEXT_CATCH 2

CollisionSystem col_sys_init(Players *const players, const double fps, const double radius) {
    CollisionSystem col_sys;
    col_sys.catch_count = 0;
    col_sys.catch_is_allowed_now = true;
    col_sys.catch_did_just_occured = false;
    col_sys.any_hit_just_occured = false;
    col_sys._players = players;
    col_sys._collisions = dyn_array_init(Collision);
    col_sys._unit_radius = radius;
    col_sys._min_ticks_before_next_catch = MIN_SECONDS_BEFORE_NEXT_CATCH * fps;
    col_sys._ticks_since_last_catch = col_sys._min_ticks_before_next_catch;
    return col_sys;
}

void col_sys_free(const CollisionSystem *const col_sys) {
    dyn_array_free(col_sys->_collisions);
}

static void resolve_hit_occurrence(CollisionSystem *const col_sys) {
    const bool hit_just_occured = dyn_array_get_length(col_sys->_collisions) != 0;
    col_sys->any_hit_just_occured = hit_just_occured;
}

static void resolve_catch_is_allowed_now(CollisionSystem *const col_sys) {
    if (col_sys->_ticks_since_last_catch < col_sys->_min_ticks_before_next_catch) {
        col_sys->_ticks_since_last_catch++;
        col_sys->catch_is_allowed_now = false;
    } else {
        col_sys->catch_is_allowed_now = true;
    }
}

static void swap_catcher_and_runner(const Collision collision) {
    const Unit previous_catcher = *collision.u1;
    *collision.u1 = *collision.u2;
    *collision.u2 = previous_catcher;
}

static void mark_catch(CollisionSystem *const col_sys) {
    col_sys->catch_did_just_occured = true;
    col_sys->catch_count++;
    col_sys->_ticks_since_last_catch = 0;
    col_sys->catch_is_allowed_now = false;
}

static void resolve_new_catcher(CollisionSystem *const col_sys) {
    if (!col_sys->catch_is_allowed_now) return;
    const size_t collisions_length = dyn_array_get_length(col_sys->_collisions);
    for (size_t i = 0; i < collisions_length; i++) {
        const Collision collision = col_sys->_collisions[i];
        const int catcher_id = players_get_catcher(col_sys->_players)->id;
        if (collision.u1->id != catcher_id) continue;
        swap_catcher_and_runner(collision);
        mark_catch(col_sys);
        break;
    }
}

static void col_sys_reset(CollisionSystem *const col_sys) {
    col_sys->catch_did_just_occured = false;
    dyn_array_clear(col_sys->_collisions);
}

void col_sys_resolve_collisions(CollisionSystem *const col_sys) {
    col_sys_reset(col_sys);
    collision_detect(col_sys->_players->all_players, &col_sys->_collisions, col_sys->_unit_radius);
    collision_resolve(col_sys->_collisions, col_sys->_unit_radius);
    resolve_hit_occurrence(col_sys);
    resolve_new_catcher(col_sys);
    resolve_catch_is_allowed_now(col_sys);
}