#include <simulation.h>
#include <dynamic_array.h>

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
    Simulation simulation;
    simulation.catch_count = 0;
    simulation.catch_did_just_occured = false;
    simulation.any_hit_just_occured = false;
    simulation.__units = init_dyn_array(Unit);
    simulation.__collisions = init_dyn_array(Collision);
    simulation.__integration_delta = 1 / fps;
    simulation.__unit_radius = unit_radius;
    simulation.__fps = fps;
    simulation.__ticks_since_last_catch = 0;
    push_dyn_array(simulation.__units, catcher);
    for (size_t i = 0; i < runners_size; i++) {
        push_dyn_array(simulation.__units, runners[i]);
    }
    return simulation;
}

Unit *simulation_get_catcher(const Simulation *const simulation) {
    return &simulation->__units[CATCHER];
}

Unit *simulation_get_runner(const Simulation *const simulation, const size_t index) {
    return &simulation->__units[RUNNERS + index];
}

void simulation_tick(Simulation *const simulation) {

}

void simulation_free(Simulation *const simulation) {
    free_dyn_array(simulation->__units);
    free_dyn_array(simulation->__collisions);
}