#ifndef AGENT_H
#define AGENT_H

#include <stdio.h>
#include "constants.h"

typedef struct
{

    // the first three states
    float p1;
    float p2;
    float p3;

    float pn1; // after CC
    float pn2; // CD
    float pn3; // DC
    float pn4; // DD

    // statistics
    // accumulated average payoff so far
    float accumAvgPayoff;

    int x, y; // grid coor

    // propensity to continue to play the next round or not
    //float propToPlay;

    Outcome lastRound;
    int roundsPlayed;
} Agent;

float randFloat();
Agent makeRandomAgent(int x, int y);
void printAgent(Agent *ag);

float distanceCost(Agent *a, Agent *b);
int continueRound(Agent *a, Agent *b, int round);
void playOneRound(float pp1, float pp2, Agent *a, Agent *b);
void playRounds(Agent *a, Agent *b);

void mutateAgent(Agent *a);

#endif
