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
    Vector _translation;
    double _scale_factor;
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
void rl_set_controller(RaylibUI *const ui, const Controller *const controller);
void rl_start(RaylibUI *const ui);
void rl_draw_unit(const RaylibUI *const ui, const Vector *const position, const bool is_catcher);
void rl_draw_score(const RaylibUI *const ui, const int score);
void rl_make_hit_sound(const RaylibUI *const ui);
void rl_make_catch_sound(const RaylibUI *const ui);
void rl_free(const RaylibUI *const ui);

#endif // RAYLIB_UI_H