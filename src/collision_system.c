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
    col_sys._collisions = init_dyn_array(Collision);
    col_sys._unit_radius = radius;
    col_sys._min_ticks_before_next_catch = MIN_SECONDS_BEFORE_NEXT_CATCH * fps;
    col_sys._ticks_since_last_catch = col_sys._min_ticks_before_next_catch;
    return col_sys;
}

void col_sys_free(const CollisionSystem *const col_sys) {
    free_dyn_array(col_sys->_collisions);
}

void col_sys_reset(CollisionSystem *const col_sys) {
    col_sys->any_hit_just_occured = false;
    col_sys->catch_did_just_occured = false;
    clear_dyn_array(col_sys->_collisions);
}

static void check_if_any_hit_occured(CollisionSystem *const col_sys) {
    if (get_length_dyn_array(col_sys->_collisions) != 0) {
        col_sys->any_hit_just_occured = true;
    }
}

static bool not_enough_time_passed_since_last_catch(const CollisionSystem *const col_sys) {
    return col_sys->_ticks_since_last_catch < col_sys->_min_ticks_before_next_catch;
}

static bool ready_to_perform_new_catch(const CollisionSystem *const col_sys) {
    return col_sys->_ticks_since_last_catch >= col_sys->_min_ticks_before_next_catch;
}

static void update_ticks_since_last_catch(CollisionSystem *const col_sys) {
    if (not_enough_time_passed_since_last_catch(col_sys)) {
        col_sys->_ticks_since_last_catch++;
    } else {
        col_sys->catch_is_allowed_now = true;
    }
}

static void resolve_new_catcher(CollisionSystem *const col_sys) {
    if (!ready_to_perform_new_catch(col_sys)) { return; }
    const size_t collisions_length = get_length_dyn_array(col_sys->_collisions);
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

void col_sys_resolve_collisions(CollisionSystem *const col_sys) {
    update_ticks_since_last_catch(col_sys);
    collision_detect(col_sys->_players->all_players, &col_sys->_collisions, col_sys->_unit_radius);
    collision_resolve(col_sys->_collisions, col_sys->_unit_radius);
    check_if_any_hit_occured(col_sys);
    resolve_new_catcher(col_sys);
}