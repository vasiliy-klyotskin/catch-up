#if !defined(RAYLIB_UI_H)
#define RAYLIB_UI_H

#include <controller.h>
#include <geometry.h>
#include <raylib.h>

typedef struct {
    Controller *_controller;
    Sound _hit_sound;
    Sound _catch_sound;
    int _width;
    int _height;
    double _unit_radius;
    double _fps;
} RaylibUI;

UI rl_ui_abstraction_init(RaylibUI *rl_ui);
RaylibUI rl_ui_init(int width, int height, double unit_radius, double fps);
void rl_set_controller(RaylibUI *self, Controller *controller);
void rl_start(RaylibUI *self);
void rl_draw_unit(RaylibUI *self, Vector *position, bool is_catcher);
void rl_draw_score(RaylibUI *self, int score);
void rl_make_hit_sound(RaylibUI *self);
void rl_make_catch_sound(RaylibUI *self);
void rl_clean(RaylibUI *self);

#endif // RAYLIB_UI_H