#if !defined(SIMULATION_H)
#define SIMULATION_H

#include <catchup_player.h>
#include <geometry.h>

typedef struct {
    CatchupPlayer *players;
} Simulation;

void init_simulation(Simulation *simulation);
void tick(Simulation *simulation);

#endif // SIMULATION_H
