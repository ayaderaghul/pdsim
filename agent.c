#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define GRID_SIZE 6
#define POP_SIZE (GRID_SIZE * GRID_SIZE)
#define ROUNDS 10
#define CYCLE 1000
#define CC 3
#define CD 0
#define DC 4
#define DD 1

// variable to store average population payoff
float avgPopPayoff =0.0f;
typedef enum { OUTCOME_CC, OUTCOME_CD, OUTCOME_DC, OUTCOME_DD } Outcome;

typedef struct {

// the first three states
float p1;
float p2;
float p3;

float pn1; // after CC
float pn2; // CD
float pn3; // DC
float pn4; // DD




// accumulated average payoff so far
float accumAvgPayoff;


int x,y ; // grid coor

float propToPlay;

Outcome lastRound;
int roundsPlayed;
} Agent;

static float randFloat(){
return (float)rand() / (float)RAND_MAX;
}
Agent makeRandomAgent(int x, int y) {
    Agent a;
    a.p1 = randFloat(); a.p2 = randFloat(); a.p3 = randFloat();
    a.pn1 = randFloat(); a.pn2 = randFloat(); a.pn3 = randFloat(); a.pn4 = randFloat();
    a.accumAvgPayoff = 0.0f;
    a.x = x; a.y = y;
    a.propToPlay = 1.0f;
    a.roundsPlayed = 0;           // FIX: initialize
    a.lastRound = OUTCOME_DD;     // FIX: sane default
    return a;
}

void printAgent(Agent *ag){
printf("Agent:\n");
    printf("p1=%.2f p2=%.2f p3=%.2f\n", ag->p1, ag->p2, ag->p3);
    printf("pn1=%.2f pn2=%.2f pn3=%.2f pn4=%.2f\n",
           ag->pn1, ag->pn2, ag->pn3, ag->pn4);
    printf("accumAvgPayoff=%.2f\n", ag->accumAvgPayoff);
printf("x, y: %d, %d\n", ag->x, ag->y);

printf("propToPlay: %.2f\n", ag->propToPlay);
printf("roundsPlayed: %d\n", ag->roundsPlayed);
printf("\n");
}

float distanceCost(Agent *a, Agent *b){
int dx = a->x - b->x;
int dy = a->y - b->y;
float fx= (float)dx;
float fy= (float)dy;
float cost = sqrtf(fx*fx + fy*fy) * 0.0005f;

//printf("cost: %.2f", cost);

return cost;
}

void play(float pp1, float pp2, int round, Agent *a, Agent *b){
int moveA = randFloat() < pp1 ? 1 : 0; // 1 = Coop
    int moveB = randFloat() < pp2 ? 1 : 0;

    int payoffA, payoffB;
    if (moveA && moveB) {
        payoffA = CC;
        payoffB = CC;
a->lastRound=0;
b->lastRound=0;
    } else if (moveA && !moveB) {
        payoffA = CD;
        payoffB = DC;

a->lastRound=1;
b->lastRound=2;
    } else if (!moveA && moveB) {
        payoffA = DC;
        payoffB = CD;
a->lastRound=2;
b->lastRound=1;
    } else {
        payoffA = DD;
        payoffB = DD;

a->lastRound=3;
b->lastRound=3;
    }

    float cost = distanceCost(a, b); // optional: grid->
    a->accumAvgPayoff = ((a->accumAvgPayoff * round) + (float)payoffA - cost)/(round +1);
    b->accumAvgPayoff = ((b->accumAvgPayoff * round)+(float)payoffB - cost)/(round+1);
a->roundsPlayed++;
b->roundsPlayed++;
}


int continueRound(Agent *a, Agent *b, int round) {
    if (round == 1) return 1; // always play first round

    float p1 = (0.4f * a->accumAvgPayoff + 0.6f * avgPopPayoff) / 4.0f;
    float p2 = (0.4f * b->accumAvgPayoff + 0.6f * avgPopPayoff) / 4.0f;

    // clamp to [0,1]
    if (p1 < 0.0f) p1 = 0.0f; if (p1 > 1.0f) p1 = 1.0f;
    if (p2 < 0.0f) p2 = 0.0f; if (p2 > 1.0f) p2 = 1.0f;

    int res1 = randFloat() < p1;
    int res2 = randFloat() < p2;

    // debug optionally:
    // printf("continue probs: a=%.3f b=%.3f -> res1=%d res2=%d\n", p1, p2, res1, res2);

    return res1 && res2;
}


// Play the first round of Prisoner's Dilemma using p1 as cooperation propensity
void playRounds(Agent *a, Agent *b) {
	int i=1;


	while(continueRound(a,b,i)==1 && i < ROUNDS) {
	
		if(i==1){
			play(a->p1, b->p1, i, a, b); 
		}

		else if (i==2){
			play(a->p2, b->p2, i, a, b);
		}

		else if (i==3){
			play(a->p3, b->p3, i, a, b);
		}
		else {
			float pp1;
			float pp2;
			if (a->lastRound == 0){
				pp1= a->pn1;
				pp2=b->pn1;
			}

			if (a->lastRound == 1){
				pp1= a->pn2;
				pp2=b->pn3;
			}
			if (a->lastRound == 2){
				pp1= a->pn3;
				pp2=b->pn2;
			}
			if (a->lastRound == 3){
				pp1= a->pn4;
				pp2=b->pn4;
			}
			play(pp1,pp2,i,a,b);
		}
		i++;
	}

}


// match the entire population for first round
void matchPopulation(Agent pop[POP_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j=j+2) {
            // match with right neighbor
            if (j + 1 < GRID_SIZE) {
                playRounds(&pop[i*GRID_SIZE+j], &pop[i*GRID_SIZE+j+1]);
            }
        }
    }
}

// compute average population payoff
float computeAvgPopPayoff(Agent pop[POP_SIZE]) {
    float total = 0.0f;
    int count = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            total += pop[i*GRID_SIZE+j].accumAvgPayoff;
            count++;
        }
    }

    return (count > 0) ? total / count : 0.0f;
}
// find the one that underplay the first time

int *findUnderplayed(Agent pop[POP_SIZE], int*size){
int*indexes = malloc(sizeof(int)* POP_SIZE);

int j=0;
for (int i=0; i <POP_SIZE;i++){
if (pop[i].roundsPlayed < ROUNDS){
indexes[j++]=i;
}
}
*size=j;
return indexes;
}

Agent* collectUnderplayedAgents(Agent* pop, int* indexes, int poolSize) {
    Agent* pool = malloc(sizeof(Agent) * poolSize);
    for (int i = 0; i < poolSize; i++) {
        pool[i] = pop[indexes[i]]; // copy agent
    }
    return pool;
}

void shufflePool(Agent* pool, int poolSize) {
    for (int i = poolSize - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Agent temp = pool[i];
        pool[i] = pool[j];
        pool[j] = temp;
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
    }
}

// regenerate

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
        newPop[k].roundsPlayed = 0;
        newPop[k].lastRound = OUTCOME_DD;
    }

    // Step 4: overwrite old population
    for (int i = 0; i < POP_SIZE; i++) {
        pop[i] = newPop[i];
    }
}
     
// mutate 

void mutate(Agent pop[POP_SIZE]) {
    int numMutations = (int)(POP_SIZE * 0.05f); // 5% of population
    if (numMutations < 1) numMutations = 1;     // at least one mutation

    for (int m = 0; m < numMutations; m++) {
        // pick a random agent
        int idx = rand() % POP_SIZE;
        Agent *a = &pop[idx];

        // pick one of the 7 propensities
        int which = rand() % 7;

        // decide +0.05 or -0.05
        float delta = (rand() % 2 == 0) ? 0.05f : -0.05f;

        float *target = NULL;
        switch (which) {
            case 0: target = &a->p1; break;
            case 1: target = &a->p2; break;
            case 2: target = &a->p3; break;
            case 3: target = &a->pn1; break;
            case 4: target = &a->pn2; break;
            case 5: target = &a->pn3; break;
            case 6: target = &a->pn4; break;
        }

        if (target) {
            *target += delta;
            if (*target < 0.0f) *target = 0.0f;
            if (*target > 1.0f) *target = 1.0f;
        }
    }
}





int main(){
	srand((unsigned)time(NULL));
	Agent population[POP_SIZE];

    // fill grid with random agents
	for (int i = 0; i < GRID_SIZE; i++) {
        	for (int j = 0; j < GRID_SIZE; j++) {
            		int index = i * GRID_SIZE + j;
            		population[index] = makeRandomAgent(i, j);
        	}
    	}

for (int c = 0; c < CYCLE; c++){
    	matchPopulation(population);


// compute average payoff
    	avgPopPayoff = computeAvgPopPayoff(population);
    	printf("Average population payoff after %d cycle: %.2f\n", c, avgPopPayoff);


    //print lst
int size;
int* lst=findUnderplayed(population, &size);


Agent* pool = collectUnderplayedAgents(population, lst, size);

shufflePool(pool,size);
rematchPool(pool,size);
refillPopulation(population,pool,lst,size);
free(pool);
free(lst);
regenerate(population);
mutate(population);


}
return 0;
}
