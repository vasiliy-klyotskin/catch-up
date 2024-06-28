#include <macroassert.h>
#include <simulation.h>

void test_simulation_init(void) {
    Unit catcher = unit_init(1, 1);
    Unit runners[2] = { unit_init(2, 3), unit_init(3, 2) };

    Simulation simulation = simulation_init(catcher, runners, 2, 1, 60);

    assert_eq(simulation.catch_count, 0);
    assert_eq(simulation.catch_did_just_occured, false);
    assert_eq(simulation.any_hit_just_occured, false);
}

void tests_simulation(void) {
    test_simulation_init();
}

