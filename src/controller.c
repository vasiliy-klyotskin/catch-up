#include <controller.h>

const Controller controller_init(const UI *const ui, Simulation *const simulation) {
    Controller controller;
    controller.__simulation = simulation;
    controller.__ui = ui;
    return controller;
}

void controller_start(const Controller *const controller) {
    const UI *const ui = controller->__ui;
    ui->start(ui->self);
}

void controller_update(const Controller *const controller) {
    const UI *const ui = controller->__ui;
    Simulation *const simulation = controller->__simulation;
    simulation_tick(simulation);
    if (simulation->any_hit_just_occured) {
        ui->make_hit_sound(ui->self);
    }
    if (simulation->catch_did_just_occured) {
        ui->make_catch_sound(ui->self);
    }
    const size_t runners_count = simulation_get_runners_count(simulation);
    const Unit *const catcher = simulation_get_catcher(simulation);
    ui->draw_unit(ui->self, &catcher->position, true);
    for (size_t i = 0; i < runners_count; i++) {
        const Unit *const runner = simulation_get_runner(simulation, i);
        ui->draw_unit(ui->self, &runner->position, false);
    }
    ui->draw_score(ui->self, simulation->catch_count);
}

void controller_add_runner(const Controller *const controller, const Vector position) {
    Simulation *const simulation = controller->__simulation;
    simulation_add_runner(simulation, position);
}

void controller_clean(const Controller *const controller) {
    const UI *const ui = controller->__ui;
    ui->clean(ui->self);
    simulation_free(controller->__simulation);
}