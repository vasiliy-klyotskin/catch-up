#if !defined(RAYLIB_UI_H)
#define RAYLIB_UI_H

#include <controller.h>
#include <geometry.h>
#include <raylib.h>

typedef struct {
    const Controller *_controller;
    Sound _hit_sound;
    Sound _catch_sound;
    int _width;
    int _height;
    double _unit_radius;
    double _fps;
} RaylibUI;

const UI rl_ui_abstraction_init(RaylibUI *const rl_ui);
RaylibUI rl_ui_init(
    const int width,
    const int height,
    const double unit_radius,
    const double fps
);
void rl_set_controller(RaylibUI *const self, const Controller *const controller);
void rl_start(RaylibUI *const self);
void rl_draw_unit(const RaylibUI *const self, const Vector *const position, const bool is_catcher);
void rl_draw_score(const RaylibUI *const self, const int score);
void rl_make_hit_sound(const RaylibUI *const self);
void rl_make_catch_sound(const RaylibUI *const self);
void rl_clean(const RaylibUI *const self);

#endif // RAYLIB_UI_H