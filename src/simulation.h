#if !defined(SIMULATION_H)
#define SIMULATION_H

#include <stdlib.h>
#include <unit.h>
#include <collision.h>
#include <stdbool.h>

typedef struct {
    int catch_count;
    bool catch_did_just_occured;
    bool any_hit_just_occured;
    Unit *_units;
    Collision *_collisions;
    Unit *_unit_to_catch;
    double _integration_delta;
    double _unit_radius;
    int _fps;
    int _min_ticks_before_next_catch;
    int _ticks_since_last_catch;
} Simulation;

Simulation simulation_init(
    Unit catcher,
    Unit *const runners,
    const size_t runners_size,
    const double unit_radius,
    const double fps
);
Unit *simulation_get_catcher(const Simulation *const s);
Unit *simulation_get_runner(const Simulation *const s, const size_t index);
size_t simulation_get_runners_count(const Simulation *const s);
void simulation_add_runner(Simulation *const s, const Vector position);
void simulation_tick(Simulation *const s);
void simulation_free(Simulation *const s);

#endif // SIMULATION_H