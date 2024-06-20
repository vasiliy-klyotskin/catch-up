#if !defined(SIMULATION_H)
#define SIMULATION_H

#include <catchup_player.h>
#include <geometry.h>

typedef struct {
    CatchupPlayer *players;
} Simulation;

void init_simulation(Simulation *simulation);
void add_tagger(Simulation *Simulation, Point position);
void add_runner(Simulation *simulation, Point position);
void tick(Simulation *simulation);

#endif // SIMULATION_H
