#include <stdlib.h>
#include <math.h>
#include "constants.h"
#include "agent.h"

float randFloat()
{
    return (float)rand() / (float)RAND_MAX;
}

Agent makeRandomAgent(int x, int y)
{
    Agent a;
    // a.p1 = randFloat();
    // a.p2 = randFloat();
    // a.p3 = randFloat();
    a.p1 = 1.0;
    a.p2=1.0;
    a.p3=1.0;

    a.pn1 = randFloat();
    a.pn2 = randFloat();
    a.pn3 = randFloat();
    a.pn4 = randFloat();
    a.accumAvgPayoff = 0.0f;
    a.x = x;
    a.y = y;
    a.propToPlay = 1.0f;
    a.roundsPlayed = 0;       // FIX: initialize
    a.lastRound = OUTCOME_DD; // FIX: sane default
    return a;
}

void printAgent(Agent *ag)
{
    printf("Agent:\n");
    printf("x, y: %d, %d\n", ag->x, ag->y);

    printf("p1=%.2f p2=%.2f p3=%.2f\n", ag->p1, ag->p2, ag->p3);

    printf("pn1=%.2f pn2=%.2f pn3=%.2f pn4=%.2f\n",
           ag->pn1, ag->pn2, ag->pn3, ag->pn4);

    printf("accumAvgPayoff=%.2f\n", ag->accumAvgPayoff);
    printf("propToPlay: %.2f\n", ag->propToPlay);
    printf("roundsPlayed: %d\n", ag->roundsPlayed);
    printf("\n");
}


float distanceCost(Agent *a, Agent *b)
{
    int dx = a->x - b->x;
    int dy = a->y - b->y;
    float fx = (float)dx;
    float fy = (float)dy;
    float cost = sqrtf(fx * fx + fy * fy) * DCOST;

    return cost;
}

int continueRound(Agent *a, Agent *b, int round)
{
    if (round == 1)
        return 1; // always play first round

    float p1 = (0.4f * a->accumAvgPayoff + 0.6f * avgPopPayoff) / 4.0f;
    float p2 = (0.4f * b->accumAvgPayoff + 0.6f * avgPopPayoff) / 4.0f;

    // clamp to [0,1]
    if (p1 < 0.0f)
        p1 = 0.0f;
    if (p1 > 1.0f)
        p1 = 1.0f;
    if (p2 < 0.0f)
        p2 = 0.0f;
    if (p2 > 1.0f)
        p2 = 1.0f;

    int res1 = randFloat() < p1;
    int res2 = randFloat() < p2;

    return res1 && res2;
}


void playOneRound(float pp1, float pp2, Agent *a, Agent *b)
{
    int moveA = randFloat() < pp1 ? 1 : 0; // 1 = Coop
    int moveB = randFloat() < pp2 ? 1 : 0;

    int payoffA, payoffB;
    if (moveA && moveB)
    {
        payoffA = CC;
        payoffB = CC;
        a->lastRound = 0;
        b->lastRound = 0;
    }
    else if (moveA && !moveB)
    {
        payoffA = CD;
        payoffB = DC;

        a->lastRound = 1;
        b->lastRound = 2;
    }
    else if (!moveA && moveB)
    {
        payoffA = DC;
        payoffB = CD;
        a->lastRound = 2;
        b->lastRound = 1;
    }
    else
    {
        payoffA = DD;
        payoffB = DD;

        a->lastRound = 3;
        b->lastRound = 3;
    }

    float cost = distanceCost(a, b);
    

    // Update agent A
    a->accumAvgPayoff =
        ((a->accumAvgPayoff * a->roundsPlayed) + (payoffA - cost)) / (a->roundsPlayed + 1);
    a->roundsPlayed++;

    // Update agent B
    b->accumAvgPayoff =
        ((b->accumAvgPayoff * b->roundsPlayed) + (payoffB - cost)) / (b->roundsPlayed + 1);
    b->roundsPlayed++;

    printf("Round %d:pp1 pp2: %.2f %.2f, move: %d vs %d, %d - %d, payoff: %d %d, accumAvgPayoff: %.2f %.2f\n", 
        a->roundsPlayed,
        pp1, pp2, moveA, moveB,
        a->lastRound, b->lastRound, payoffA, payoffB, 
        a->accumAvgPayoff, b->accumAvgPayoff);

        
    // printAgent(a);
    // printAgent(b);
}

// Play the first round of Prisoner's Dilemma using p1 as cooperation propensity
void playRounds(Agent *a, Agent *b) {
	int i=1;


	while(continueRound(a,b,i)==1 && i < ROUNDS) {
	
		if(i==1){
			playOneRound(a->p1, b->p1, a, b); 
		}

		else if (i==2){
			playOneRound(a->p2, b->p2, a, b);
		}

		else if (i==3){
			playOneRound(a->p3, b->p3, a, b);
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
			playOneRound(pp1,pp2,a,b);
		}
		i++;
	}

}

void mutateAgent(Agent *a) {
    // pick one of the 7 propensities
    int which = rand() % 7;

    // decide +0.05 or -0.05
    float delta = (rand() % 2 == 0) ? 0.05f : -0.05f;

    // pick target field
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

    // apply mutation with clamping
    if (target) {
        *target += delta;
        if (*target < 0.0f) *target = 0.0f;
        if (*target > 1.0f) *target = 1.0f;
    }
}