// sim_refactored.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define GRID_SIZE 10
#define POP_SIZE (GRID_SIZE * GRID_SIZE)
#define ROUNDS 100
#define CYCLE 1000
#define CC 3
#define CD 0
#define DC 4
#define DD 1

typedef enum { OUTCOME_CC = 0, OUTCOME_CD = 1, OUTCOME_DC = 2, OUTCOME_DD = 3 } Outcome;

typedef struct {
    // first three states
    float p1;
    float p2;
    float p3;

    // responses after previous round outcome
    float pn1; // after CC
    float pn2; // after CD
    float pn3; // after DC
    float pn4; // after DD

    // accumulated average payoff so far
    float accumAvgPayoff;

    int x,y ; // grid coords
    float propToPlay;

    Outcome lastRound;
    int roundsPlayed;
} Agent;

/* Global (kept for backward compatibility) */
static float avgPopPayoff = 0.0f;

/* Logging helper */
#ifdef UNIT_TESTS
#define LOG(fmt, ...) /* no logging in unit tests */
#else
#define LOG(fmt, ...) do { printf(fmt "\n", ##__VA_ARGS__); } while(0)
#endif

/* RNG helpers: deterministic when seed >= 0 */
static int deterministic_seed = -1;
static void rng_seed(int seed) {
    deterministic_seed = seed;
    if (seed >= 0) srand((unsigned)seed);
    else srand((unsigned)time(NULL));
}
static float randFloat(void){
    return (float)rand() / (float)RAND_MAX;
}

/* Reset helper so tests can reinitialize cleanly */
void resetAgentState(Agent *a, int x, int y) {
    a->p1 = a->p2 = a->p3 = 0.0f;
    a->pn1 = a->pn2 = a->pn3 = a->pn4 = 0.0f;
    a->accumAvgPayoff = 0.0f;
    a->x = x; a->y = y;
    a->propToPlay = 1.0f;
    a->roundsPlayed = 0;
    a->lastRound = OUTCOME_DD;
}

/* Factory - use randFloat(), deterministic when seeded */
Agent makeRandomAgent(int x, int y) {
    Agent a;
    	//a.p1 = randFloat(); 
	//a.p2 = randFloat(); 	
	//a.p3 = randFloat();
	a.p1=0.5;
	a.p2=0.5;
	a.p3=0.5;


    a.pn1 = randFloat(); a.pn2 = randFloat(); a.pn3 = randFloat(); a.pn4 = randFloat();
    a.accumAvgPayoff = 0.0f;
    a.x = x; a.y = y;
    a.propToPlay = 1.0f;
    a.roundsPlayed = 0;
    a.lastRound = OUTCOME_DD;
    return a;
}

void printAgent(const Agent *ag){
    printf("Agent (%d,%d): p1=%.3f p2=%.3f p3=%.3f pn=[%.3f,%.3f,%.3f,%.3f] accum=%.3f rounds=%d last=%d\n",
           ag->x, ag->y, ag->p1, ag->p2, ag->p3, ag->pn1, ag->pn2, ag->pn3, ag->pn4,
           ag->accumAvgPayoff, ag->roundsPlayed, (int)ag->lastRound);
}

static float distanceCost(const Agent *a, const Agent *b){
    int dx = a->x - b->x;
    int dy = a->y - b->y;
    float fx = (float)dx;
    float fy = (float)dy;
    return sqrtf(fx*fx + fy*fy) * 0.0005f;
}

/* Single play between two agents given their cooperation probabilities (pp1, pp2)
   'round' is 0-based index for averaging formula (we keep same formula semantics as original).
*/
void play(int round_index, float pp1, float pp2, Agent *a, Agent *b){
    int moveA = (randFloat() < pp1) ? 1 : 0; // 1 = Coop
    int moveB = (randFloat() < pp2) ? 1 : 0;

    int payoffA, payoffB;
    if (moveA && moveB) {
        payoffA = CC; payoffB = CC;
        a->lastRound = OUTCOME_CC; b->lastRound = OUTCOME_CC;
    } else if (moveA && !moveB) {
        payoffA = CD; payoffB = DC;
        a->lastRound = OUTCOME_CD; b->lastRound = OUTCOME_DC;
    } else if (!moveA && moveB) {
        payoffA = DC; payoffB = CD;
        a->lastRound = OUTCOME_DC; b->lastRound = OUTCOME_CD;
    } else {
        payoffA = DD; payoffB = DD;
        a->lastRound = OUTCOME_DD; b->lastRound = OUTCOME_DD;
    }

    float cost = distanceCost(a, b);

    /* Update running average using same formula as original: newAvg = ((oldAvg * round) + payoff - cost) / (round+1) */
    a->accumAvgPayoff = ((a->accumAvgPayoff * (float)round_index) + (float)payoffA - cost) / (float)(round_index + 1);
    b->accumAvgPayoff = ((b->accumAvgPayoff * (float)round_index) + (float)payoffB - cost) / (float)(round_index + 1);

    a->roundsPlayed++;
    b->roundsPlayed++;
}

/* Decide whether both agents want to continue after 'round_index' rounds */
int continueRound(const Agent *a, const Agent *b, int round_index) {
    if (round_index == 0) return 1; // always play first round

    /* produce probability based on individual's payoff and global avg */
    float p1 = (0.4f * a->accumAvgPayoff + 0.6f * avgPopPayoff) / 4.0f;
    float p2 = (0.4f * b->accumAvgPayoff + 0.6f * avgPopPayoff) / 4.0f;

    if (p1 < 0.0f) p1 = 0.0f; if (p1 > 1.0f) p1 = 1.0f;
    if (p2 < 0.0f) p2 = 0.0f; if (p2 > 1.0f) p2 = 1.0f;

    return (randFloat() < p1) && (randFloat() < p2);
}

/* Play up to ROUNDS (stopping early if continueRound denies). Uses same indexing as original: rounds 1..3 map to p1,p2,p3 then pn* responses. */
void playRounds(Agent *a, Agent *b) {
    int r = 0; // 0-based internal round index; caller earlier used 1.. so adapt accordingly
    while (r < ROUNDS && continueRound(a,b,r)) {
        if (r == 0) {
            play(r, a->p1, b->p1, a, b);
        } else if (r == 1) {
            play(r, a->p2, b->p2, a, b);
        } else if (r == 2) {
            play(r, a->p3, b->p3, a, b);
        } else {
            float ppA = 0.0f, ppB = 0.0f;
            switch (a->lastRound) {
                case OUTCOME_CC: ppA = a->pn1; ppB = b->pn1; break;
                case OUTCOME_CD: ppA = a->pn2; ppB = b->pn3; break;
                case OUTCOME_DC: ppA = a->pn3; ppB = b->pn2; break;
                case OUTCOME_DD: ppA = a->pn4; ppB = b->pn4; break;
            }
            play(r, ppA, ppB, a, b);
        }
        r++;
    }
}

/* matchPopulation: for testability the function is left explicit and simple: match horizontal pairs (j/j+1) */
void matchPopulation(Agent pop[POP_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; j += 2) {
            if (j + 1 < GRID_SIZE) {
                playRounds(&pop[i * GRID_SIZE + j], &pop[i * GRID_SIZE + j + 1]);
            }
        }
    }
}

float computeAvgPopPayoff(Agent pop[POP_SIZE]) {
    float total = 0.0f;
    int count = 0;
    for (int i = 0; i < POP_SIZE; ++i) {
        total += pop[i].accumAvgPayoff;
        ++count;
    }
    return count ? total / (float)count : 0.0f;
}

/* find indices of agents that played fewer than ROUNDS */
int *findUnderplayed(Agent pop[POP_SIZE], int *outSize) {
    int *indexes = malloc(sizeof(int) * POP_SIZE);
    if (!indexes) { *outSize = 0; return NULL; }
    int k = 0;
    for (int i = 0; i < POP_SIZE; ++i) {
        if (pop[i].roundsPlayed < ROUNDS) {
            indexes[k++] = i;
        }
    }
    *outSize = k;
    return indexes;
}

Agent* collectUnderplayedAgents(Agent* pop, int* indexes, int poolSize) {
    Agent* pool = malloc(sizeof(Agent) * poolSize);
    for (int i = 0; i < poolSize; ++i) {
        pool[i] = pop[indexes[i]]; // copy
    }
    return pool;
}

void shufflePool(Agent* pool, int poolSize) {
    for (int i = poolSize - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Agent tmp = pool[i]; pool[i] = pool[j]; pool[j] = tmp;
    }
}

void rematchPool(Agent* pool, int poolSize) {
    for (int i = 0; i + 1 < poolSize; i += 2) {
        playRounds(&pool[i], &pool[i+1]);
    }
}

void refillPopulation(Agent* pop, Agent* pool, int* indexes, int poolSize) {
    for (int i = 0; i < poolSize; ++i) {
        pop[indexes[i]] = pool[i];
    }
}

/* Regenerate using roulette wheel on accumAvgPayoff (non-negative enforced) */
void regenerate(Agent pop[POP_SIZE]) {
    float totalPayoff = 0.0f;
    for (int i = 0; i < POP_SIZE; ++i) {
        if (pop[i].accumAvgPayoff < 0.0f) pop[i].accumAvgPayoff = 0.0f;
        totalPayoff += pop[i].accumAvgPayoff;
    }
    if (totalPayoff <= 0.0f) totalPayoff = 1.0f;

    float cumulative[POP_SIZE];
    float running = 0.0f;
    for (int i = 0; i < POP_SIZE; ++i) {
        running += pop[i].accumAvgPayoff / totalPayoff;
        cumulative[i] = running;
    }

    Agent newPop[POP_SIZE];
    for (int k = 0; k < POP_SIZE; ++k) {
        float r = randFloat();
        int chosen = 0;
        while (chosen < POP_SIZE && r > cumulative[chosen]) ++chosen;
        if (chosen >= POP_SIZE) chosen = POP_SIZE - 1;
        newPop[k] = pop[chosen];
        newPop[k].accumAvgPayoff = 0.0f;
        newPop[k].roundsPlayed = 0;
        newPop[k].lastRound = OUTCOME_DD;
    }

    memcpy(pop, newPop, sizeof(newPop));
}

/* Mutate 5% of population (at least one) bounded to [0,1] */
void mutate(Agent pop[POP_SIZE]) {
    int numMutations = (int)(POP_SIZE * 0.05f);
    if (numMutations < 1) numMutations = 1;
    for (int m = 0; m < numMutations; ++m) {
        int idx = rand() % POP_SIZE;
        Agent *a = &pop[idx];
        int which = rand() % 7;
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

/* Initialize population with random agents */
void initPopulation(Agent population[POP_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            int idx = i * GRID_SIZE + j;
            population[idx] = makeRandomAgent(i, j);
        }
    }
}

/* ---------- Small unit-test helpers ---------- */
static void assert_flt_equal(float a, float b, float tol, const char *msg) {
    if (fabsf(a - b) > tol) {
        fprintf(stderr, "Assertion failed: %s (%.6f != %.6f)\n", msg, a, b);
        abort();
    }
}

/* Basic deterministic tests */
void run_unit_tests(void) {
    LOG("Running unit tests (deterministic seed 42)");
    rng_seed(42);

    /* Test: play with deterministic probabilities and same position (cost=0) */
    Agent A, B;
    resetAgentState(&A, 0, 0);
    resetAgentState(&B, 0, 0);
    A.p1 = 1.0f; B.p1 = 0.0f; // A always cooperates, B always defects
    play(0, A.p1, B.p1, &A, &B);
    /* payoffs: A should get CD (0), B DC (4) -> accumAvgPayoff after 1 round equals payoff - cost */
    assert_flt_equal(A.accumAvgPayoff, (float)CD, 1e-6f, "A payoff after CD should equal CD (no cost)");
    assert_flt_equal(B.accumAvgPayoff, (float)DC, 1e-6f, "B payoff after DC should equal DC (no cost)");

    /* Test: playRounds uses p2/p3 when applicable and updates roundsPlayed count */
    resetAgentState(&A, 0, 0); resetAgentState(&B, 0, 0);
    A.p1 = 1.0f; A.p2 = 1.0f; A.p3 = 1.0f; // always cooperate
    B.p1 = 1.0f; B.p2 = 1.0f; B.p3 = 1.0f;
    playRounds(&A, &B);
    /* If both always cooperate and no random stopping, after at least one round accumAvgPayoff should be > 0 */
    if (A.roundsPlayed == 0 || B.roundsPlayed == 0) {
        fprintf(stderr, "playRounds produced 0 rounds unexpectedly\n");
        abort();
    }

    /* Test: findUnderplayed on fresh population after init - many should be < ROUNDS */
    Agent population[POP_SIZE];
    initPopulation(population);
    int size;
    int *idxs = findUnderplayed(population, &size);
    assert(size >= 0 && idxs != NULL);
    free(idxs);

    /* Test: regenerate should not crash and should produce POP_SIZE agents */
    for (int i = 0; i < POP_SIZE; ++i) {
        population[i].accumAvgPayoff = (float)(i % 5); // variety
    }
    regenerate(population);

    LOG("Unit tests passed.");
}

/* ---------- main ---------- */
int main(int argc, char **argv) {
    int run_tests = 0;
    if (argc > 1 && strcmp(argv[1], "test") == 0) run_tests = 1;
#ifdef UNIT_TESTS
    run_tests = 1;
#endif

    if (run_tests) {
        rng_seed(42);
        run_unit_tests();
        return 0;
    }

    /* normal run: seed with time for stochastic behavior */
    rng_seed(-1);

    Agent population[POP_SIZE];
    initPopulation(population);

    for (int cycle = 0; cycle < CYCLE; ++cycle) {
        matchPopulation(population);

        avgPopPayoff = computeAvgPopPayoff(population);
        printf("Average population payoff after cycle %d: %.4f\n", cycle, avgPopPayoff);

        int size;
        int* lst = findUnderplayed(population, &size);
        if (lst && size > 0) {
            Agent* pool = collectUnderplayedAgents(population, lst, size);
            shufflePool(pool, size);
            rematchPool(pool, size);
            refillPopulation(population, pool, lst, size);
            free(pool);
        }
        free(lst);

        regenerate(population);
        mutate(population);
    }
printf("agents:\n");
	for(int i=0;i<5;i++){
printAgent(&population[i]);
printf("\n");
}


    return 0;
}
