#include <simulation.h>
#include <dynamic_array.h>
#include <unit.h>
#include <time.h>
#include <util.h>

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
#define MIN_SECONDS_BEFORE_NEXT_CATCH 2

enum UnitsLayout {
    CATCHER,
    RUNNERS
};

Simulation simulation_init(
    Unit catcher,
    Unit *const runners,
    const size_t runners_size,
    const double unit_radius,
    const double fps
) {
    srand(time(NULL));
    Simulation s;
    s.catch_count = 0;
    s.catch_did_just_occured = false;
    s.any_hit_just_occured = false;
    s._units = init_dyn_array(Unit);
    s._collisions = init_dyn_array(Collision);
    s._random_accels = random_accels_init(rand_minus1_1, RANDOM_UPDATE_DELAY, RANDOM_ACCEL_RUNNER_COEF);
    s._unit_to_catch = NULL;
    s._integration_delta = 1 / fps;
    s._unit_radius = unit_radius;
    s._min_ticks_before_next_catch = MIN_SECONDS_BEFORE_NEXT_CATCH * fps;
    s._ticks_since_last_catch = s._min_ticks_before_next_catch;
    push_dyn_array(s._units, catcher);
    for (size_t i = 0; i < runners_size; i++) {
        push_dyn_array(s._units, runners[i]);
    }
    return s;
}

Unit *simulation_get_catcher(const Simulation *const s) {
    return &s->_units[CATCHER];
}

Unit *simulation_get_runner(const Simulation *const s, const size_t index) {
    return &s->_units[RUNNERS + index];
}

size_t simulation_get_runners_count(const Simulation *const s) {
    return get_length_dyn_array(s->_units) - RUNNERS;
}

void simulation_add_runner(Simulation *const s, const Vector position) {
    push_rval_dyn_array(s->_units, Unit, unit_init(position.x, position.y));
    random_accels_add(&s->_random_accels);
}

static void check_if_any_hit_occured(Simulation *const s) {
    if (get_length_dyn_array(s->_collisions) != 0) {
        s->any_hit_just_occured = true;
    }
}

static void simulation_reset(Simulation *const s) {
    s->any_hit_just_occured = false;
    s->catch_did_just_occured = false;
    s->_unit_to_catch = NULL;
    clear_dyn_array(s->_collisions);
}

static bool not_enough_time_passed_since_last_catch(Simulation *const s) {
    return s->_ticks_since_last_catch < s->_min_ticks_before_next_catch;
}

static bool ready_to_perform_new_catch(Simulation *const s) {
    return s->_ticks_since_last_catch == s->_min_ticks_before_next_catch;
}

static void update_ticks_since_last_catch(Simulation *const s) {
    if (not_enough_time_passed_since_last_catch(s)) {
        s->_ticks_since_last_catch++;
    }
}

static void resolve_new_catcher(Simulation *const s) {
    if (!ready_to_perform_new_catch(s)) { return; }
    const size_t collisions_length = get_length_dyn_array(s->_collisions);
    for (size_t i = 0; i < collisions_length; i++) {
        const Collision collision = s->_collisions[i];
        if (collision.u1->id == simulation_get_catcher(s)->id) {
            const Unit previous_catcher = *collision.u1;
            *collision.u1 = *collision.u2;
            *collision.u2 = previous_catcher;
            s->catch_did_just_occured = true;
            s->catch_count++;
            s->_ticks_since_last_catch = 0;
            break;
        }
    }
}

static void resolve_catcher_movement(Simulation *const s) {
    const Unit *const unit_to_catch = s->_unit_to_catch;
    Unit *const catcher = simulation_get_catcher(s);
    reset_velocity_when_low(catcher, CATCHER_VELOCITY_RESET_THRESHOLD);
    if (ready_to_perform_new_catch(s) && (unit_to_catch != NULL)) {
        set_catch_velocity(
            catcher,
            unit_to_catch,
            CATCHER_MAX_VELOCITY,
            CATCHER_VELOCITY_INCR_COEF,
            CATCHER_ANGLE_FITTING_COEF
        );
    } else {
        add_friction_accel(catcher, 2 * FRICTION_COEF);
    }
}

static void resolve_unit_to_catch_if_needed(Simulation *const s) {
    if (!ready_to_perform_new_catch(s)) return;
    Unit *const catcher = simulation_get_catcher(s);
    s->_unit_to_catch = find_nearest(catcher, s->_units);
}

static void resolve_unit_to_catch_movement(Simulation *s) {
    Unit *const unit_to_catch = s->_unit_to_catch;
    if (unit_to_catch != NULL) {
        add_return_to_middle_accel(unit_to_catch, 0.75 * RETURN_TO_MIDDLE_COEF);
    }
}

static void resolve_runners_movement(Simulation *const s) {
    resolve_unit_to_catch_movement(s);
    Unit *const catcher = simulation_get_catcher(s);
    const size_t units_length = get_length_dyn_array(s->_units);
    for (size_t i = RUNNERS; i < units_length; i++) {
        Unit *const runner = &s->_units[i];
        add_friction_accel(runner, FRICTION_COEF);
        add_return_to_middle_accel(runner, RETURN_TO_MIDDLE_COEF);
        add_run_away_accel(runner, catcher, RUN_AWAY_COEF);
        add_accel(runner, random_accels_get(&s->_random_accels, i - RUNNERS));
        for (size_t k = RUNNERS; k < units_length; k++) {
            const Unit *const neighbor = &s->_units[k];
            if (neighbor->id == runner->id) continue;
            add_repulsion_accel(runner, neighbor, REPULSION_COEF);
        }
    }
}

static void resolve_movement(Simulation *const s) {
    reset_accel(s->_units);
    resolve_unit_to_catch_if_needed(s);
    resolve_catcher_movement(s);
    random_accels_update(&s->_random_accels);
    resolve_runners_movement(s);
    do_euler_integration(s->_units, s->_integration_delta);
}

void simulation_tick(Simulation *const s) {
    simulation_reset(s);
    update_ticks_since_last_catch(s);
    detect_collisions(s->_units, &s->_collisions, s->_unit_radius);
    resolve_collisions(s->_collisions, s->_unit_radius);
    check_if_any_hit_occured(s);
    resolve_new_catcher(s);
    resolve_movement(s);
}

void simulation_free(Simulation *const s) {
    free_dyn_array(s->_units);
    free_dyn_array(s->_collisions);
    random_accels_free(&s->_random_accels);
}