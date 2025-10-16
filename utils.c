#include "constants.h"
#include "agent.h"
#include "utils.h"




// compute average population payoff
float computeAvgPopPayoff(Agent pop[POP_SIZE])
{
    float total = 0.0f;
    int count = 0;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            total += pop[i * GRID_SIZE + j].accumAvgPayoff;
            count++;
        }
    }

    return (count > 0) ? total / count : 0.0f;
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
