#include <stdlib.h>
#include "constants.h"
#include "agent.h"
#include "population.h"
static void shuffleArray(Agent *array, int n) {
    for(int i=n-1;i>0;i--) {
        int j = rand()% (i+1);
        Agent tmp=array[i]; array[i]=array[j]; array[j]=tmp;
    }
}
// match the entire population for first round
void matchPopulation(Agent pop[POP_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j=j+2) {
            // match with right neighbor
            if (j + 1 < GRID_SIZE) {
                // printf("Play rounds between i & j: %d %d:\n", i*GRID_SIZE+ j, i*GRID_SIZE+j+1);
                // printAgent(&pop[i]);
                // printAgent(&pop[j]);
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

void regenerate(Agent pop[POP_SIZE]){
    // Roulette wheel selection based on payoff
    float total=0.0f;
    for(int i=0;i<POP_SIZE;i++){if(pop[i].accumAvgPayoff<0.0f)pop[i].accumAvgPayoff=0.0f;total+=pop[i].accumAvgPayoff;}
    if(total==0.0f) total=1.0f;
    float cumulative[POP_SIZE]; float running=0.0f;
    for(int i=0;i<POP_SIZE;i++){running+=pop[i].accumAvgPayoff/total;cumulative[i]=running;}
    Agent newPop[POP_SIZE];
    for(int k=0;k<POP_SIZE;k++){
        float r=randFloat();
        int chosen=0; while(chosen<POP_SIZE && r>cumulative[chosen]) chosen++;
        if(chosen>=POP_SIZE)chosen=POP_SIZE-1;
        newPop[k]=pop[chosen];
        newPop[k].accumAvgPayoff=0.0f;
        newPop[k].roundsPlayed=0;
    }
    for(int i=0;i<POP_SIZE;i++) pop[i]=newPop[i];
    shuffleArray(pop,POP_SIZE);
    mutate(pop);
}

void mutate(Agent pop[POP_SIZE]) {
    int numMutations = (int)(POP_SIZE * 0.05f); // 5% of population
    if (numMutations < 1) numMutations = 1;     // at least one mutation

    for (int m = 0; m < numMutations; m++) {
        int idx = rand() % POP_SIZE;
        mutateAgent(&pop[idx]);
    }
}
