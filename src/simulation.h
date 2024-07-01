#if !defined(SIMULATION_H)
#define SIMULATION_H

#include <stdlib.h>
#include <unit.h>
#include <collision.h>
#include <stdbool.h>

typedef struct {
    double catch_count;
    bool catch_did_just_occured;
    bool any_hit_just_occured;
    Unit *__units;
    Collision *__collisions;
    Unit *__unit_to_catch;
    double __integration_delta;
    double __unit_radius;
    double __fps;
    double __min_ticks_before_next_catch;
    int __ticks_since_last_catch;
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
void simulation_add_runner(Simulation *const s, const Vector position);
void simulation_tick(Simulation *const s);
void simulation_free(Simulation *const s);

#endif // SIMULATION_H