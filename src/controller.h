#if !defined(CONTROLLER_H)
#define CONTROLLER_H

#include <geometry.h>
#include <simulation.h>

typedef void (*StartFn)(void *self);
typedef void (*DrawUnitFn)(void *self, Vector *position, bool is_catcher);
typedef void (*DrawScoreFn)(void *self, int score);
typedef void (*MakeHitSoundFn)(void *self);
typedef void (*MakeCatchSoundFn)(void *self);
typedef void (*CleanFn)(void *self);

typedef struct {
    void *self;
    StartFn start;
    DrawUnitFn draw_unit;
    DrawScoreFn draw_score;
    MakeHitSoundFn make_hit_sound;
    MakeCatchSoundFn make_catch_sound;
    CleanFn clean;
} UI;

typedef struct {
    UI *__ui;
    Simulation *__simulation;
} Controller;

Controller controller_init(UI *ui, Simulation *simulation);
void controller_start(Controller *controller);
void controller_update(Controller *controller);
void controller_add_runner(Controller *controller, Vector position);
void controller_clean(Controller *controller);

#endif // CONTROLLER_H
