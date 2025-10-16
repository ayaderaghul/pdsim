#ifndef CONSTANTS_H
#define CONSTANTS_H

// Grid and population constants
#define GRID_SIZE 10
#define POP_SIZE (GRID_SIZE * GRID_SIZE)
#define ROUNDS 100
#define CYCLE 10000
#define DCOST 0.0f // 0.005f

// Payoff values
#define CC 3
#define CD 0
#define DC 4
#define DD 1

// Global variables (defined in constants.c)
extern double mutation_rate;
extern float avgPopPayoff;

// Type definitions
typedef enum { OUTCOME_CC, OUTCOME_CD, OUTCOME_DC, OUTCOME_DD } Outcome;
#endif