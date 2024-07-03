#include <controller.h>
#include <raylib_ui.h>

#define FPS 60
#define UNIT_RADIUS 0.03
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700

int main(void) {
    const Unit catcher = unit_init(0, 0);
    Simulation simulation = simulation_init(catcher, NULL, 0, UNIT_RADIUS, FPS);
    RaylibUI rl_ui = rl_ui_init(SCREEN_WIDTH, SCREEN_HEIGHT, UNIT_RADIUS, FPS);
    const UI ui = rl_ui_abstraction_init(&rl_ui);
    const Controller controller = controller_init(&ui, &simulation);
    rl_set_controller(&rl_ui, &controller);
    controller_start(&controller);
}