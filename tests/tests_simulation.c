#include <macroassert.h>
#include <simulation.h>

#define FPS 60

void test_simulation_get_catcher(void) {
    Unit catcher_input = unit_init(1, 2);
    Unit runners[0] = {};
    Simulation s = simulation_init(catcher_input, runners, 0, 1, FPS);

    Unit *catcher = simulation_get_catcher(&s);

    assert_eq(catcher->position.x, 1);
    assert_eq(catcher->position.y, 2);
}

void test_simulation_get_runner(void) {
    Unit catcher_input = unit_init(1, 2);
    Unit runners[2] = { unit_init(3, 4), unit_init(5, 6) };
    Simulation s = simulation_init(catcher_input, runners, 2, 1, FPS);

    Unit *runner1 = simulation_get_runner(&s, 0);
    assert_eq(runner1->position.x, 3);
    assert_eq(runner1->position.y, 4);

    Unit *runner2 = simulation_get_runner(&s, 1);
    assert_eq(runner2->position.x, 5);
    assert_eq(runner2->position.y, 6);
}

void test_simulation_when_hit_occures_between_runners(void) {
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

void test_simulation_when_catch_occures(void) {
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

void tests_simulation(void) {
    test_simulation_get_catcher();
    test_simulation_get_runner();
    test_simulation_when_hit_occures_between_runners();
    test_simulation_when_catch_occures();
}