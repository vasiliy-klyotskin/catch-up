#if !defined(SIMULATION_H)
#define SIMULATION_H

#include <catchup_unit.h>

typedef struct {
    CatchupUnit *units;
    int size;
} Simulation;

void tick(Simulation *simulation);

#endif // SIMULATION_H
