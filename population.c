#include <stdlib.h>
#include "constants.h"
#include "agent.h"
#include "population.h"

// match the entire population for first round
void matchPopulation(Agent pop[POP_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j=j+2) {
            // match with right neighbor
            if (j + 1 < GRID_SIZE) {
               // printf("Play rounds: i & j: %d %d:\n", i, j);
                playRounds(&pop[i*GRID_SIZE+j], &pop[i*GRID_SIZE+j+1]);
               // printf("\n");
            }
        }
    }
}

void rematchPool(Agent* pool, int poolSize) {
    for (int i = 0; i + 1 < poolSize; i += 2) {
        Agent* a = &pool[i];
        Agent* b = &pool[i + 1];

        // Play until dropout or maxRounds
        playRounds(a,b);
    }
}
void refillPopulation(Agent* pop, Agent* pool, int* indexes, int poolSize) {
    for (int i = 0; i < poolSize; i++) {
        pop[indexes[i]] = pool[i]; // overwrite with updated agent
	pop[indexes[i]].x = i / GRID_SIZE;
	pop[indexes[i]].y=i%GRID_SIZE;
    }
}

void regenerate(Agent pop[POP_SIZE]) {
    // Step 1: total payoff
    float totalPayoff = 0.0f;
    for (int i = 0; i < POP_SIZE; i++) {
        if (pop[i].accumAvgPayoff < 0.0f) pop[i].accumAvgPayoff = 0.0f; // enforce non-negative fitness
        totalPayoff += pop[i].accumAvgPayoff;
    }
    if (totalPayoff == 0.0f) totalPayoff = 1.0f;

    // Step 2: cumulative distribution
    float cumulative[POP_SIZE];
    float running = 0.0f;
    for (int i = 0; i < POP_SIZE; i++) {
        running += pop[i].accumAvgPayoff / totalPayoff;
        cumulative[i] = running;
    }

    // Step 3: build new population (roulette wheel)
    Agent newPop[POP_SIZE];
    for (int k = 0; k < POP_SIZE; k++) {
        float r = randFloat();
        int chosen = 0;
        while (chosen < POP_SIZE && r > cumulative[chosen]) chosen++;
        if (chosen >= POP_SIZE) chosen = POP_SIZE - 1;

        newPop[k] = pop[chosen];

        // Reset state for next generation
        newPop[k].accumAvgPayoff = 0.0f;
printf("rounds play %d: %d\n", k, newPop[k].roundsPlayed);
        newPop[k].roundsPlayed = 0;
        newPop[k].lastRound = OUTCOME_DD;
	newPop[k].x= k/GRID_SIZE;
	newPop[k].y=k%GRID_SIZE;
    }

    // Step 4: overwrite old population
    for (int i = 0; i < POP_SIZE; i++) {
        pop[i] = newPop[i];
    }
}

void mutate(Agent pop[POP_SIZE]) {
    int numMutations = (int)(POP_SIZE * 0.05f); // 5% of population
    if (numMutations < 1) numMutations = 1;     // at least one mutation

    for (int m = 0; m < numMutations; m++) {
        int idx = rand() % POP_SIZE;
        mutateAgent(&pop[idx]);
    }
}
