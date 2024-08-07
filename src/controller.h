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
} UI;

typedef struct {
    const UI *_ui;
    Simulation *_simulation;
    int _max_runners;
} Controller;

const Controller controller_init(const UI *const ui, Simulation *const simulation, const int max_runners);
void controller_start(const Controller *const controller);
void controller_update(const Controller *const controller);
void controller_add_runner(const Controller *const controller, const Vector position);

#endif // CONTROLLER_H
