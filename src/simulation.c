#include <simulation.h>
#include <util.h>

Simulation simulation_init(const double unit_radius, const double fps) {
    Simulation s;
    s.players = players_init();
    s._mv_sys = mv_sys_init(rand_minus1_1, &s.players, 1 / fps);
    s._col_sys = col_sys_init(&s.players, fps, unit_radius);
    return s;
}

SimulationInfo simulation_get_info(const Simulation *const s) {
    SimulationInfo vm;
    vm.any_hit_just_occured = s->_col_sys.any_hit_just_occured;
    vm.catch_count = s->_col_sys.catch_count;
    vm.catch_did_just_occured = s->_col_sys.catch_did_just_occured;
    return vm;
}

void simulation_add_runner(Simulation *const s, const Vector position) {
    players_add_runner(&s->players, position);
}

void simulation_free(const Simulation *const s) {
    players_free(&s->players);
    mv_sys_free(&s->_mv_sys);
    col_sys_free(&s->_col_sys);
}

void simulation_tick(Simulation *const s) {
    col_sys_reset(&s->_col_sys);
    mv_sys_reset(&s->_mv_sys);
    col_sys_resolve_collisions(&s->_col_sys);
    mv_sys_resolve_movement(&s->_mv_sys, s->_col_sys.catch_is_allowed_now);
}