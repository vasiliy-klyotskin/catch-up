#include <controller.h>
#include <raylib_ui.h>

#define FPS 60
#define UNIT_RADIUS 12
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define SCALE 1

int main(void) {
    Unit catcher = unit_init(0, 0);
    Simulation simulation = simulation_init(catcher, NULL, 0, UNIT_RADIUS, FPS);
    RaylibUI rl_ui = rl_ui_init(SCREEN_WIDTH, SCREEN_HEIGHT, UNIT_RADIUS, FPS);
    UI ui = rl_ui_abstraction_init(&rl_ui);
    Controller controller = controller_init(&ui, &simulation);
    controller_start(&controller);
}