#include <controller.h>

Controller controller_init(UI *ui, Simulation *simulation) {
    Controller controller;
    controller.__simulation = simulation;
    controller.__ui = ui;
    return controller;
}

void controller_start(Controller *controller) {
    UI *ui = controller->__ui;
    ui->start(ui->self);
}

void controller_update(Controller *controller) {
    UI *ui = controller->__ui;
    Simulation *simulation = controller->__simulation;
    simulation_tick(simulation);
    size_t runners_count = simulation_get_runners_count(simulation);
    Unit *catcher = simulation_get_catcher(simulation);
    ui->draw_unit(ui->self, &catcher->position, true);
    for (size_t i = 0; i < runners_count; i++) {
        Unit *runner = simulation_get_runner(simulation, i);
        ui->draw_unit(ui->self, &runner->position, false);
    }
    if (simulation->any_hit_just_occured) {
        ui->make_hit_sound(ui->self);
    }
    if (simulation->catch_did_just_occured) {
        ui->make_catch_sound(ui->self);
    }
    ui->draw_score(ui->self, simulation->catch_count);
}

void controller_add_runner(Controller *controller, Vector position) {
    Simulation *simulation = controller->__simulation;
    simulation_add_runner(simulation, position);
}

void controller_clean(Controller *controller) {
    UI *ui = controller->__ui;
    ui->clean(ui->self);
    simulation_free(controller->__simulation);
}