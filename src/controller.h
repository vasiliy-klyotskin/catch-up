#if !defined(CONTROLLER_H)
#define CONTROLLER_H

#include <geometry.h>
#include <simulation.h>

typedef void (*StartFn)(void *self);
typedef void (*DrawUnitFn)(void *self, const Vector *const position, const bool is_catcher);
typedef void (*DrawScoreFn)(void *self, const int score);
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

const Controller controller_init(UI *const ui, Simulation *const simulation);
void controller_start(const Controller *const controller);
void controller_update(const Controller *const controller);
void controller_add_runner(const Controller *const controller, const Vector position);
void controller_clean(const Controller *const controller);

#endif // CONTROLLER_H
