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

static void check_if_any_hit_occured(CollisionSystem *const col_sys) {
    if (dyn_array_get_length(col_sys->_collisions) != 0) {
        col_sys->any_hit_just_occured = true;
    }
}

static void update_catch_is_allowed_now(CollisionSystem *const col_sys) {
    if (col_sys->_ticks_since_last_catch < col_sys->_min_ticks_before_next_catch) {
        col_sys->_ticks_since_last_catch++;
        col_sys->catch_is_allowed_now = false;
    } else {
        col_sys->catch_is_allowed_now = true;
    }
}

static void resolve_new_catcher(CollisionSystem *const col_sys) {
    if (!col_sys->catch_is_allowed_now) { return; }
    const size_t collisions_length = dyn_array_get_length(col_sys->_collisions);
    for (size_t i = 0; i < collisions_length; i++) {
        const Collision collision = col_sys->_collisions[i];
        const Unit *const catcher = players_get_catcher(col_sys->_players);
        if (collision.u1->id == catcher->id) {
            const Unit previous_catcher = *collision.u1;
            *collision.u1 = *collision.u2;
            *collision.u2 = previous_catcher;
            col_sys->catch_did_just_occured = true;
            col_sys->catch_count++;
            col_sys->_ticks_since_last_catch = 0;
            col_sys->catch_is_allowed_now = false;
            break;
        }
    }
}

static void col_sys_reset(CollisionSystem *const col_sys) {
    col_sys->any_hit_just_occured = false;
    col_sys->catch_did_just_occured = false;
    dyn_array_clear(col_sys->_collisions);
}

void col_sys_resolve_collisions(CollisionSystem *const col_sys) {
    col_sys_reset(col_sys);
    collision_detect(col_sys->_players->all_players, &col_sys->_collisions, col_sys->_unit_radius);
    collision_resolve(col_sys->_collisions, col_sys->_unit_radius);
    check_if_any_hit_occured(col_sys);
    resolve_new_catcher(col_sys);
    update_catch_is_allowed_now(col_sys);
}