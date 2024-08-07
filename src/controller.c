#include <controller.h>

const Controller controller_init(const UI *const ui, Simulation *const simulation, const int max_runners) {
    Controller controller;
    controller._simulation = simulation;
    controller._ui = ui;
    controller._max_runners = max_runners;
    return controller;
}

void controller_start(const Controller *const controller) {
    const UI *const ui = controller->_ui;
    ui->start(ui->self);
}

static void present_units(const Controller *const controller) {
    const UI *const ui = controller->_ui;
    const Players *const players = &controller->_simulation->players;
    const size_t runners_count = players_runners_count(players);
    const Unit *const catcher = players_get_catcher(players);
    ui->draw_unit(ui->self, &catcher->position, true);
    for (size_t i = 0; i < runners_count; i++) {
        const Unit *const runner = players_get_runner(players, i);
        ui->draw_unit(ui->self, &runner->position, false);
    }
}

static void make_sounds(const Controller *const controller) {
    const UI *const ui = controller->_ui;
    const SimulationInfo info = simulation_get_info(controller->_simulation);
    if (info.any_hit_just_occured) {
        ui->make_hit_sound(ui->self);
    }
    if (info.catch_did_just_occured) {
        ui->make_catch_sound(ui->self);
    }
}

void present_score(const Controller *const controller) {
    const UI *const ui = controller->_ui;
    const SimulationInfo info = simulation_get_info(controller->_simulation);
    ui->draw_score(ui->self, info.catch_count);
}

void controller_update(const Controller *const controller) {
    simulation_tick(controller->_simulation);
    make_sounds(controller);
    present_units(controller);
    present_score(controller);
}

void controller_add_runner(const Controller *const controller, const Vector position) {
    Simulation *const simulation = controller->_simulation;
    if (players_runners_count(&simulation->players) >= controller->_max_runners) return;
    simulation_add_runner(simulation, position);
}