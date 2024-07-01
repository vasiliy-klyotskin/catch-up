#include <macroassert.h>
#include <simulation.h>

#define FPS 60

void do_ticks(const Simulation *const s, const double count) {
    for (size_t i = 0; i < count; i++) {
        simulation_tick(s);
    }
}

void add_runner_colliding_with_catcher(Simulation *const s) {
    Vector catcher_pos1 = simulation_get_catcher(s)->position;
    Vector new_colliding_runner1 = vector_init(catcher_pos1.x + 0.01, catcher_pos1.y + 0.01);
    simulation_add_runner(s, new_colliding_runner1);
}

void test_simulation_get_catcher(void) {
    Unit catcher_input = unit_init(1, 2);
    Unit runners[0] = {};
    Simulation s = simulation_init(catcher_input, runners, 0, 1, FPS);

    Unit *catcher = simulation_get_catcher(&s);

    assert_eq(catcher->position.x, 1);
    assert_eq(catcher->position.y, 2);
}

void test_simulation_get_add_runner(void) {
    Unit catcher_input = unit_init(1, 2);
    Unit runners[0] = {};
    Simulation s = simulation_init(catcher_input, runners, 0, 1, FPS);
    simulation_add_runner(&s, vector_init(3, 4));
    simulation_add_runner(&s, vector_init(5, 6));

    Unit *runner1 = simulation_get_runner(&s, 0);
    assert_eq(runner1->position.x, 3);
    assert_eq(runner1->position.y, 4);

    Unit *runner2 = simulation_get_runner(&s, 1);
    assert_eq(runner2->position.x, 5);
    assert_eq(runner2->position.y, 6);
}

void test_simulation_tick_when_hit_occures_between_runners(void) {
    Unit catcher_input = unit_init(5, 5);
    Unit runners[2] = { unit_init(0, 0), unit_init(1.99, 0) };
    double unit_radius = 1;
    Simulation s = simulation_init(catcher_input, runners, 2, unit_radius, FPS);

    assert_eq(s.any_hit_just_occured, false);

    simulation_tick(&s);
    assert_eq(s.any_hit_just_occured, true);

    simulation_tick(&s);
    assert_eq(s.any_hit_just_occured, false);
}

void test_simulation_tick_when_catch_occures(void) {
    Unit catcher = unit_init(0, 0);
    double high_velocity = 100;
    catcher.velocity.x = high_velocity;
    Unit runners[1] = { unit_init(1.99, 0) };
    double unit_radius = 1;
    Simulation s = simulation_init(catcher, runners, 1, unit_radius, FPS);

    assert_eq(s.catch_did_just_occured, false);
    assert_eq(s.any_hit_just_occured, false);
    assert_eq(simulation_get_runner(&s, 0)->id, runners[0].id);
    assert_eq(simulation_get_catcher(&s)->id, catcher.id);

    simulation_tick(&s);
    assert_eq(s.catch_did_just_occured, true);
    assert_eq(s.any_hit_just_occured, true);
    assert_eq(simulation_get_runner(&s, 0)->id, catcher.id);
    assert_eq(simulation_get_catcher(&s)->id, runners[0].id);

    simulation_tick(&s);
    assert_eq(s.catch_did_just_occured, false);
    assert_eq(s.any_hit_just_occured, false);
    assert_eq(simulation_get_runner(&s, 0)->id, catcher.id);
    assert_eq(simulation_get_catcher(&s)->id, runners[0].id);
}

void test_simulation_tick_catch_cant_occure_right_after_previous(void) {
    Unit catcher = unit_init(0.01, 0);
    Unit runners[1] = { unit_init(1.99, 0) };
    double unit_radius = 1;
    Simulation s = simulation_init(catcher, runners, 1, unit_radius, FPS);

    simulation_tick(&s);
    assert_eq(s.catch_did_just_occured, true);

    int min_seconds_before_next_catch = 2;
    do_ticks(&s, min_seconds_before_next_catch * FPS - 1);
    add_runner_colliding_with_catcher(&s);
    simulation_tick(&s);
    assert_eq(s.catch_did_just_occured, false);

    add_runner_colliding_with_catcher(&s);
    simulation_tick(&s);
    assert_eq(s.catch_did_just_occured, true);
}

void tests_simulation(void) {
    test_simulation_get_catcher();
    test_simulation_get_add_runner();
    test_simulation_tick_when_hit_occures_between_runners();
    test_simulation_tick_when_catch_occures();
    test_simulation_tick_catch_cant_occure_right_after_previous();
}