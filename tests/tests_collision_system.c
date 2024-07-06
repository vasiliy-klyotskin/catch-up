#include <macroassert.h>
#include <collision_system.h>
#include <players.h>

#define FPS 60
#define MIN_SECONDS_BEFORE_NEXT_CATCH 2

static void do_resolutions(CollisionSystem *const col_sys, const double count) {
    for (size_t i = 0; i < count; i++) {
        col_sys_resolve_collisions(col_sys);
    }
}

static void reposition_catcher_to_any_position(Players *const players) {
    Unit *const catcher = players_get_catcher(players);
    catcher->position.x = 4124;
    catcher->velocity.y = 7242;
}

static void add_runner_colliding_with_catcher(Players *const players) {
    Vector catcher_pos1 = players_get_catcher(players)->position;
    Vector new_colliding_runner1 = vector_init(catcher_pos1.x + 0.01, catcher_pos1.y + 0.01);
    players_add_runner(players, new_colliding_runner1);
}

static void test_system_when_hit_occures_between_runners(void) {
    Players players = players_init();
    players_add_runner(&players, vector_init(0, 5));
    players_add_runner(&players, vector_init(1.99, 5));
    const double unit_radius = 1;
    CollisionSystem col_sys = col_sys_init(&players, FPS, unit_radius);

    assert_eq(col_sys.any_hit_just_occured, false);

    col_sys_resolve_collisions(&col_sys);
    assert_eq(col_sys.any_hit_just_occured, true);

    col_sys_resolve_collisions(&col_sys);
    assert_eq(col_sys.any_hit_just_occured, false);
}

static void test_system_when_catch_occures(void) {
    Players players = players_init();
    players_add_runner(&players, vector_init(1.99, 0));
    const Unit *const runner = players_get_runner(&players, 0);
    Unit *const catcher = players_get_catcher(&players);
    const int init_catcher_id = catcher->id;
    const int init_runner_id = runner->id;
    const double unit_radius = 1;
    CollisionSystem col_sys = col_sys_init(&players, FPS, unit_radius);

    assert_eq(col_sys.catch_did_just_occured, false);
    assert_eq(col_sys.any_hit_just_occured, false);
    assert_eq(col_sys.catch_is_allowed_now, true);
    assert_eq(col_sys.catch_count, 0);
    assert_eq(players_get_runner(&players, 0)->id, init_runner_id);
    assert_eq(players_get_catcher(&players)->id, init_catcher_id);

    col_sys_resolve_collisions(&col_sys);
    assert_eq(col_sys.catch_did_just_occured, true);
    assert_eq(col_sys.any_hit_just_occured, true);
    assert_eq(col_sys.catch_is_allowed_now, false);
    assert_eq(col_sys.catch_count, 1);
    assert_eq(players_get_runner(&players, 0)->id, init_catcher_id);
    assert_eq(players_get_catcher(&players)->id, init_runner_id);

    do_resolutions(&col_sys, MIN_SECONDS_BEFORE_NEXT_CATCH * FPS - 1);
    add_runner_colliding_with_catcher(&players);
    const int colliding_unit_id_1 = players_get_runner(&players, 1)->id;
    col_sys_resolve_collisions(&col_sys);
    assert_eq(col_sys.catch_did_just_occured, false);
    assert_eq(col_sys.any_hit_just_occured, true);
    assert_eq(col_sys.catch_is_allowed_now, true);
    assert_eq(col_sys.catch_count, 1);
    assert_eq(players_get_runner(&players, 1)->id, colliding_unit_id_1);
    assert_eq(players_get_catcher(&players)->id, init_runner_id);

    reposition_catcher_to_any_position(&players);
    add_runner_colliding_with_catcher(&players);
    const int colliding_unit_id_2 = players_get_runner(&players, 2)->id;
    col_sys_resolve_collisions(&col_sys);
    assert_eq(col_sys.catch_did_just_occured, true);
    assert_eq(col_sys.any_hit_just_occured, true);
    assert_eq(col_sys.catch_is_allowed_now, false);
    assert_eq(col_sys.catch_count, 2);
    assert_eq(players_get_runner(&players, 2)->id, init_runner_id);
    assert_eq(players_get_catcher(&players)->id, colliding_unit_id_2);
}

void tests_collision_system(void) {
    test_system_when_hit_occures_between_runners();
    test_system_when_catch_occures();
}