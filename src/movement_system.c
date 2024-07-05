#include <movement_system.h>
#include <dynamic_array.h>
#include <movement.h>

#define REPULSION_COEF 0.06
#define RETURN_TO_MIDDLE_COEF 4
#define FRICTION_COEF 2
#define RUN_AWAY_COEF 0.6
#define RANDOM_ACCEL_RUNNER_COEF 0.85
#define RANDOM_UPDATE_DELAY 100
#define CATCHER_VELOCITY_RESET_THRESHOLD 0.008
#define CATCHER_MAX_VELOCITY 0.88
#define CATCHER_VELOCITY_INCR_COEF 0.01
#define CATCHER_ANGLE_FITTING_COEF 0.09

MovementSystem mv_sys_init(
    RandFnMinus1To1 rand,
    Players *const players,
    const double integration_delta
) {
    MovementSystem mv_sys;
    mv_sys._players = players;
    mv_sys._integration_delta = integration_delta;
    mv_sys._random_accels = random_accels_init(rand, RANDOM_UPDATE_DELAY, RANDOM_ACCEL_RUNNER_COEF);
    mv_sys._unit_to_catch = NULL;
    return mv_sys;
}

void mv_sys_free(const MovementSystem *const mv_sys) {
    random_accels_free(&mv_sys->_random_accels);
}

static void resolve_catcher_movement(const MovementSystem *const mv_sys, const bool need_to_catch) {
    const Unit *const unit_to_catch = mv_sys->_unit_to_catch;
    Unit *const catcher = players_get_catcher(mv_sys->_players);
    unit_reset_velocity_when_low(catcher, CATCHER_VELOCITY_RESET_THRESHOLD);
    if (need_to_catch && (unit_to_catch != NULL)) {
        unit_set_catch_velocity(
            catcher,
            unit_to_catch,
            CATCHER_MAX_VELOCITY,
            CATCHER_VELOCITY_INCR_COEF,
            CATCHER_ANGLE_FITTING_COEF
        );
    } else {
        unit_add_friction_accel(catcher, 2 * FRICTION_COEF);
    }
}

static void resolve_unit_to_catch(MovementSystem *const mv_sys) {
    Unit *const catcher = players_get_catcher(mv_sys->_players);
    mv_sys->_unit_to_catch = unit_find_nearest(catcher, mv_sys->_players->all_players);
}

static void resolve_unit_to_catch_movement(const MovementSystem *const mv_sys) {
    Unit *const unit_to_catch = mv_sys->_unit_to_catch;
    if (unit_to_catch == NULL) return;
    if (players_runners_count(mv_sys->_players) < 2) return;
    unit_add_return_to_middle_accel(unit_to_catch, 0.75 * RETURN_TO_MIDDLE_COEF);
}

static void mv_sys_add_repulsion_accel(const MovementSystem *const mv_sys, Unit *const runner) {
    const size_t runners_count = players_runners_count(mv_sys->_players);
    for (size_t k = 0; k < runners_count; k++) {
        const Unit *const neighbor = players_get_runner(mv_sys->_players, k);
        if (neighbor->id == runner->id) continue;
        unit_add_repulsion_accel(runner, neighbor, REPULSION_COEF);
    }
}

static void resolve_runners_movement(const MovementSystem *const mv_sys) {
    resolve_unit_to_catch_movement(mv_sys);
    Unit *const catcher = players_get_catcher(mv_sys->_players);
    const size_t runners_count = players_runners_count(mv_sys->_players);
    for (size_t i = 0; i < runners_count; i++) {
        Unit *const runner = players_get_runner(mv_sys->_players, i);
        unit_add_friction_accel(runner, FRICTION_COEF);
        unit_add_return_to_middle_accel(runner, RETURN_TO_MIDDLE_COEF);
        unit_add_run_away_accel(runner, catcher, RUN_AWAY_COEF);
        unit_add_accel(runner, random_accels_get(&mv_sys->_random_accels, i));
        mv_sys_add_repulsion_accel(mv_sys, runner);
    }
}

static void add_random_accels_if_needed(MovementSystem *const mv_sys) {
    const size_t runners_count = players_runners_count(mv_sys->_players);
    const size_t accels_count = random_accels_get_count(&mv_sys->_random_accels);
    for (size_t i = 0; i < runners_count - accels_count; i++) {
        random_accels_add(&mv_sys->_random_accels);
    }
}

void mv_sys_resolve_movement(MovementSystem *const mv_sys, const bool need_to_catch) {
    unit_reset_accel(mv_sys->_players->all_players);
    if (need_to_catch) resolve_unit_to_catch(mv_sys);
    if (false) resolve_catcher_movement(mv_sys, need_to_catch);
    add_random_accels_if_needed(mv_sys);
    random_accels_update(&mv_sys->_random_accels);
    resolve_runners_movement(mv_sys);
    unit_do_euler_integration(mv_sys->_players->all_players, mv_sys->_integration_delta);
}

void mv_sys_reset(MovementSystem *const mv_sys) {
    mv_sys->_unit_to_catch = NULL;
}