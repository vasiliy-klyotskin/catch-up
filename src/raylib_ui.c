#include <raylib_ui.h>
#include <raylib.h>
#include <controller.h>
#include <stdio.h>

const UI rl_ui_abstraction_init(RaylibUI *const rl_ui){
    UI ui;
    ui.start = (StartFn)rl_start;
    ui.draw_unit = (DrawUnitFn)rl_draw_unit;
    ui.draw_score = (DrawScoreFn)rl_draw_score;
    ui.make_catch_sound = (MakeCatchSoundFn)rl_make_catch_sound;
    ui.make_hit_sound = (MakeHitSoundFn)rl_make_hit_sound;
    ui.clean = (CleanFn)rl_clean;
    ui.self = rl_ui;
    return ui;
}

RaylibUI rl_ui_init(const int width, const int height, const double unit_radius, const double fps) {
    RaylibUI rl_ui;
    rl_ui._width = width;
    rl_ui._height = height;
    rl_ui._unit_radius = unit_radius;
    rl_ui._fps = fps;
    rl_ui._controller = NULL;
    return rl_ui;
}

void rl_set_controller(RaylibUI *const self, const Controller *const controller) {
    self->_controller = controller;
}

static void rl_prepare(RaylibUI *const self) {
    SetTargetFPS(self->_fps);
    InitWindow(self->_width, self->_height, "catch-up");
    InitAudioDevice();
    self->_hit_sound = LoadSound("resources/hit.wav");
    self->_catch_sound = LoadSound("resources/catch.wav");
}

static void rl_add_runner_if_user_clicked_mlb(const RaylibUI *const self) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        const Vector2 position = GetMousePosition();
        const double x = (position.x - self->_width / 2) / (self->_width / 2);
        const double y = (position.y - self->_width / 2) / (self->_width / 2);
        controller_add_runner(self->_controller, vector_init(x, y));
    }
}

void rl_start(RaylibUI *const self) {
    rl_prepare(self);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        rl_add_runner_if_user_clicked_mlb(self);
        controller_update(self->_controller);
        EndDrawing();
    }
    controller_clean(self->_controller);
}

void rl_draw_unit(const RaylibUI *const self, const Vector *const position, const bool is_catcher) {
    const double x = position->x * (self->_width / 2) + self->_width / 2;
    const double y = position->y * (self->_width / 2) + self->_width / 2;
    const Color unit_color = is_catcher ? PINK : SKYBLUE;
    DrawCircle(x, y, self->_unit_radius * (self->_width / 2), unit_color);
}

void rl_draw_score(const RaylibUI *const self, int score) {
    char text[20];
    sprintf(text, "Catches: %d", score);
    DrawText(text, self->_width / 10, self->_height / 10, 20, LIGHTGRAY);
}

void rl_make_hit_sound(const RaylibUI *const self) {
    PlaySound(self->_hit_sound);
}

void rl_make_catch_sound(const RaylibUI *const self) {
    PlaySound(self->_catch_sound);
}

void rl_clean(const RaylibUI *const self) {
    CloseWindow();
    CloseAudioDevice();
}