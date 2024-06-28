#include <simulation.h>
#include <dynamic_array.h>

Simulation simulation_init(
    const Unit catcher,
    const Unit *const runners,
    const size_t runners_size,
    const double unit_radius,
    const double fps
) {
    Simulation simulation;
    simulation.any_hit_just_occured = false;
    simulation.catch_did_just_occured = false;
    simulation.catch_count = 0;
    simulation.__units = init_dyn_array(Unit);
    push_dyn_array(simulation.__units, catcher);
    return simulation;
}

Unit *simulation_get_catcher(const Simulation *const simulation) {
    return &simulation->__units[0];
}

Unit *simulation_get_runner(const Simulation *const simulation, const size_t index) {

}

void tick(const Simulation *const simulation) {

}