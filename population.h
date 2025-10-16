#ifndef POPULATION_H
#define POPULATION_H

#include "constants.h"
#include "agent.h"

void matchPopulation(Agent pop[POP_SIZE]);
void rematchPool(Agent* pool, int poolSize);
void refillPopulation(Agent* pop, Agent* pool, int* indexes, int poolSize);
void regenerate(Agent pop[POP_SIZE]);
void mutate(Agent pop[POP_SIZE]);

#endif