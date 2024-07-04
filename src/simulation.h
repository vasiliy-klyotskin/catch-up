#if !defined(SIMULATION_H)
#define SIMULATION_H

#include <movement_system.h>
#include <collision_system.h>
#include <stdbool.h>

typedef struct {
    int catch_count;
    bool catch_did_just_occured;
    bool any_hit_just_occured;
} SimulationInfo;

typedef struct {
    Players players;
    MovementSystem _mv_sys;
    CollisionSystem _col_sys;
} Simulation;

Simulation simulation_init(const double unit_radius, const double fps);
SimulationInfo simulation_get_info(const Simulation *const s);
void simulation_tick(Simulation *const s);
void simulation_add_runner(Simulation *const s, const Vector position);
void simulation_free(const Simulation *const s);

#endif // SIMULATION_H