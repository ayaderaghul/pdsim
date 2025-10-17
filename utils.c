#include "constants.h"
#include "agent.h"
#include "utils.h"




float computeAvgPopPayoffScaled(Agent pop[POP_SIZE]) {
    float sum = 0.0f;
    for (int i = 0; i < POP_SIZE; i++) {
        if (pop[i].roundsPlayed > 0)
            sum += pop[i].accumAvgPayoff; // already per-round
    }
    return sum / POP_SIZE;
}
// find the one that underplay the first time

int *findUnderplayed(Agent pop[POP_SIZE], int *size)
{
    int *indexes = malloc(sizeof(int) * POP_SIZE);

    int j = 0;
    for (int i = 0; i < POP_SIZE; i++)
    {
        if (pop[i].roundsPlayed < ROUNDS)
        {
            indexes[j++] = i;
        }
    }
    *size = j;
    return indexes;
}

Agent *collectUnderplayedAgents(Agent *pop, int *indexes, int poolSize)
{
    Agent *pool = malloc(sizeof(Agent) * poolSize);
    for (int i = 0; i < poolSize; i++)
    {
        pool[i] = pop[indexes[i]]; // copy agent
    }
    return pool;
}

// Fisher-Yates shuffle
void shufflePool(Agent *pool, int poolSize)
{
    for (int i = poolSize - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Agent temp = pool[i];
        pool[i] = pool[j];
        pool[j] = temp;
    }
}


