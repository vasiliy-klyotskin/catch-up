#include <raylib_ui.h>
#include <raylib.h>
#include <controller.h>
#include <stdio.h>

UI rl_ui_abstraction_init(RaylibUI *rl_ui){
    UI ui;
    ui.start = (StartFn)rl_start;
    ui.draw_unit = (DrawUnitFn)rl_draw_unit;
    ui.draw_score = (DrawScoreFn)rl_draw_score;
    ui.make_catch_sound = (MakeCatchSoundFn)rl_make_catch_sound;
    ui.make_hit_sound = (MakeHitSoundFn)rl_make_hit_sound;
    ui.clean = (CleanFn)rl_clean;
    ui.self = &rl_ui;
    return ui;
}

RaylibUI rl_ui_init(int width, int height, double unit_radius, double scale, double fps) {
    RaylibUI rl_ui;
    rl_ui._width = width;
    rl_ui._height = height;
    rl_ui._unit_radius = unit_radius;
    rl_ui._scale = scale;
    rl_ui._fps = fps;
    rl_ui._controller = NULL;
}

void rl_set_controller(RaylibUI *self, Controller *controller) {
    self->_controller = controller;
}

void rl_prepare(RaylibUI *self) {
    SetTargetFPS(self->_fps);
    InitWindow(self->_width, self->_height, "catch-up");
    self->_hit_sound = LoadSound("resources/hit.wav");
    self->_catch_sound = LoadSound("resources/catch.wav");
}

void rl_add_runner_if_user_clicked_mlb(RaylibUI *self) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 position = GetMousePosition();
        controller_add_runner(self->_controller, vector_init(position.x, position.y));
    }
}

void rl_start(RaylibUI *self) {
    rl_prepare(self);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        rl_add_runner_if_user_clicked_mlb(self);
        controller_update(self->_controller);
        EndDrawing();
    }
    controller_clean(self->_controller);
}

void rl_draw_unit(RaylibUI *self, Vector *position, bool is_catcher) {
    Color unit_color = is_catcher ? RED : BLUE;
    DrawCircle(position->x, position->y, self->_unit_radius, unit_color);
}

void rl_draw_score(RaylibUI *self, int score) {
    char text[20];
    sprintf(text, "Catches: %d", score);
    DrawText(text, self->_width / 10, self->_height / 10, 20, LIGHTGRAY);
}

void rl_make_hit_sound(RaylibUI *self) {
    PlaySound(self->_hit_sound);
}

void rl_make_catch_sound(RaylibUI *self) {
    PlaySound(self->_catch_sound);
}

void rl_clean(RaylibUI *self) {
    CloseWindow();
}