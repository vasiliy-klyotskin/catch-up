#if !defined(RAYLIB_UI_H)
#define RAYLIB_UI_H

#include <controller.h>
#include <geometry.h>

typedef struct {
    Controller *_controller;
    int _screen_width;
    int _screen_height;
    double _unit_radius;
    double _scale;
    double _fps;
} RaylibUI;

UI rl_init();
void rl_set_controller(Controller *controller);
void rl_start(RaylibUI *self);
void rl_draw_unit(RaylibUI *self, Vector *position);
void rl_draw_score(RaylibUI *self);
void rl_make_hit_sound(RaylibUI *self);
void rl_make_catch_sound(RaylibUI *self);
void rl_clean(RaylibUI *self);

#endif // RAYLIB_UI_H
