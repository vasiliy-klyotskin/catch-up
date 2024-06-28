#include <simulation.h>

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
    return simulation;
}

Unit *simulation_get_catcher(void) {

}

Unit *simulation_get_runner(const size_t index) {

}

void tick(const Simulation *const simulation) {

}