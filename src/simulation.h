#if !defined(SIMULATION_H)
#define SIMULATION_H

#include <catchup_player.h>
#include <geometry.h>

typedef struct {
    CatchupPlayer *units;
    int size;
} Simulation;

void initSimulation(Simulation *simulation);
void addRunner(Simulation *simulation, Point position);
void tick(Simulation *simulation);

#endif // SIMULATION_H
