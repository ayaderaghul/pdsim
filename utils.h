#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include "agent.h"



float computeAvgPopPayoffScaled(Agent pop[POP_SIZE]);
int *findUnderplayed(Agent pop[POP_SIZE], int *size);
Agent *collectUnderplayedAgents(Agent *pop, int *indexes, int poolSize);
void shufflePool(Agent *pool, int poolSize);

#endif