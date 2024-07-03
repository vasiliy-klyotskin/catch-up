#include <raylib_ui.h>
#include <raylib.h>
#include <controller.h>
#include <stdio.h>
#include <math.h>

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

static double min(double a, double b) {
    return (a < b) ? a : b;
}

RaylibUI rl_ui_init(const int width, const int height, const double unit_radius, const double fps) {
    RaylibUI rl_ui;
    rl_ui._width = width;
    rl_ui._height = height;
    rl_ui._translation = vector_init(width * 0.5, height * 0.5);
    rl_ui._scale_factor = min(width, height) * 0.5;
    rl_ui._unit_radius = unit_radius;
    rl_ui._fps = fps;
    rl_ui._controller = NULL;
    return rl_ui;
}

void rl_set_controller(RaylibUI *const ui, const Controller *const controller) {
    ui->_controller = controller;
}

static void rl_prepare(RaylibUI *const ui) {
    SetTraceLogLevel(LOG_NONE);
    SetTargetFPS(ui->_fps);
    InitWindow(ui->_width, ui->_height, "catch-up");
    InitAudioDevice();
    ui->_hit_sound = LoadSound("resources/hit.wav");
    ui->_catch_sound = LoadSound("resources/catch.wav");
}

static Vector rl_transform_coordinate_to_simulation(const RaylibUI *const ui, const Vector2 rl_coord) {
    const Vector coord = vector_init(rl_coord.x, rl_coord.y);
    const Vector translated_back = vector_difference(&ui->_translation, &coord);
    return vector_scaled(&translated_back, 1 / ui->_scale_factor);
}

static void rl_add_runner_if_user_clicked_mlb(const RaylibUI *const ui) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        const Vector unit_position = rl_transform_coordinate_to_simulation(ui, GetMousePosition());
        controller_add_runner(ui->_controller, unit_position);
    }
}

void rl_start(RaylibUI *const ui) {
    rl_prepare(ui);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        rl_add_runner_if_user_clicked_mlb(ui);
        controller_update(ui->_controller);
        EndDrawing();
    }
    controller_clean(ui->_controller);
}

static Vector rl_transform_coordinate_from_simulation(const RaylibUI *const ui, const Vector *const coord) {
    const Vector scaled = vector_scaled(coord, ui->_scale_factor);
    return vector_sum(&scaled, &ui->_translation);
}

void rl_draw_unit(const RaylibUI *const ui, const Vector *const position, const bool is_catcher) {
    const Vector unit_position = rl_transform_coordinate_from_simulation(ui, position);
    const Color unit_color = is_catcher ? PINK : SKYBLUE;
    const double radius = ui->_unit_radius * ui->_scale_factor;
    DrawCircle(
        round(unit_position.x),
        round(unit_position.y),
        radius,
        unit_color
    );
}

void rl_draw_score(const RaylibUI *const ui, int score) {
    char text[20];
    sprintf(text, "Catches: %d", score);
    DrawText(text, ui->_width / 10, ui->_height / 10, 20, LIGHTGRAY);
}

void rl_make_hit_sound(const RaylibUI *const ui) {
    PlaySound(ui->_hit_sound);
}

void rl_make_catch_sound(const RaylibUI *const ui) {
    PlaySound(ui->_catch_sound);
}

void rl_clean(const RaylibUI *const ui) {
    CloseWindow();
    CloseAudioDevice();
}