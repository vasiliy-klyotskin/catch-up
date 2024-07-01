#include <simulation.h>
#include <dynamic_array.h>
#include <collision.h>
#include <limits.h>
#include <stdio.h>

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
    Simulation s;
    s.catch_count = 0;
    s.catch_did_just_occured = false;
    s.any_hit_just_occured = false;
    s.__units = init_dyn_array(Unit);
    s.__collisions = init_dyn_array(Collision);
    s.__integration_delta = 1 / fps;
    s.__unit_radius = unit_radius;
    s.__fps = fps;
    s.__ticks_before_next_catch = 2 * fps;
    s.__ticks_since_last_catch = s.__ticks_before_next_catch;
    push_dyn_array(s.__units, catcher);
    for (size_t i = 0; i < runners_size; i++) {
        push_dyn_array(s.__units, runners[i]);
    }
    return s;
}

Unit *simulation_get_catcher(const Simulation *const s) {
    return &s->__units[CATCHER];
}

Unit *simulation_get_runner(const Simulation *const s, const size_t index) {
    return &s->__units[RUNNERS + index];
}

void simulation_add_runner(Simulation *const s, const Vector position) {
    push_rval_dyn_array(s->__units, Unit, unit_init(position.x, position.y));
}

void check_if_any_hit_occured(Simulation *const s) {
    if (get_length_dyn_array(s->__collisions) != 0) {
        s->any_hit_just_occured = true;
    }
}

void simulation_reset(Simulation *const s) {
    s->any_hit_just_occured = false;
    s->catch_did_just_occured = false;
    clear_dyn_array(s->__collisions);
}

void resolve_new_catcher(Simulation *const s) {
    if (s->__ticks_since_last_catch < s->__ticks_before_next_catch) {
        s->__ticks_since_last_catch++;
        return;
    }
    size_t collisions_length = get_length_dyn_array(s->__collisions);
    for (size_t i = 0; i < collisions_length; i++) {
        Collision collision = s->__collisions[i];
        if (collision.u1->id == simulation_get_catcher(s)->id) {
            Unit previous_catcher = *collision.u1;
            *collision.u1 = *collision.u2;
            *collision.u2 = previous_catcher;
            s->catch_did_just_occured = true;
            s->__ticks_since_last_catch = 0;
            break;
        }
    }
}

void simulation_tick(Simulation *const s) {
    simulation_reset(s);
    detect_collisions(s->__units, s->__collisions, s->__unit_radius);
    check_if_any_hit_occured(s);
    resolve_collisions(s->__collisions, s->__unit_radius);
    resolve_new_catcher(s);
}

void simulation_free(Simulation *const simulation) {
    free_dyn_array(simulation->__units);
    free_dyn_array(simulation->__collisions);
}