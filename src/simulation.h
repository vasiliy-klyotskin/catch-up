#if !defined(SIMULATION_H)
#define SIMULATION_H

#include <unit.h>
#include <geometry.h>

typedef struct {
    Unit *players;
} Simulation;

void init_simulation(Simulation *simulation);
void tick(Simulation *simulation);

#endif // SIMULATION_H
