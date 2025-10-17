#include <stdio.h>
#include <stdlib.h>
#include "agent.h"
#include "constants.h"

int parseAgent(const char *str, Agent *a) {
    // Example input:
    // Agent: x, y: 5, 8. p1=0.46 p2=0.41 p3=0.54. pn1=0.56 pn2=0.05 pn3=0.05 pn4=0.00. accumAvgPayoff=0.00. roundsPlayed: 0.

    int parsed = sscanf(str,
        "Agent: x, y: %d, %d. p1=%f p2=%f p3=%f. "
        "pn1=%f pn2=%f pn3=%f pn4=%f. "
        "accumAvgPayoff=%f. roundsPlayed: %d.",
        &a->x, &a->y,
        &a->p1, &a->p2, &a->p3,
        &a->pn1, &a->pn2, &a->pn3, &a->pn4,
        &a->accumAvgPayoff, &a->roundsPlayed
    );

    if (parsed != 11) {
        fprintf(stderr, "❌ Failed to parse agent from string: %s\n", str);
        return 0; // failure
    }

    // No lastRound info in this format, so default it
    a->lastRound = OUTCOME_DD;

    return 1; // success
}



void playAndPrintHistory(Agent *a, Agent *b, int rounds) {
    char historyA[rounds + 1];
    char historyB[rounds + 1];

    // Copy last round outcomes so strategies evolve correctly
    Outcome last = (a->lastRound == OUTCOME_DD) ? OUTCOME_CC : a->lastRound;

    for (int r = 0; r < rounds; r++) {
        float pa, pb;

        // Agent A’s probability depends on last outcome
        switch (last) {
            case OUTCOME_CC: pa = a->pn1; pb = b->pn1; break;
            case OUTCOME_CD: pa = a->pn2; pb = b->pn3; break;
            case OUTCOME_DC: pa = a->pn3; pb = b->pn2; break;
            case OUTCOME_DD: pa = a->pn4; pb = b->pn4; break;
            default:         pa = a->p1;  pb = b->p1;  break; // initial
        }

        int moveA = (randFloat() < pa) ? 1 : 0;
        int moveB = (randFloat() < pb) ? 1 : 0;

        historyA[r] = moveA ? 'C' : 'D';
        historyB[r] = moveB ? 'C' : 'D';

        // Update last outcome for both
        if (moveA && moveB) last = OUTCOME_CC;
        else if (moveA && !moveB) last = OUTCOME_CD;
        else if (!moveA && moveB) last = OUTCOME_DC;
        else last = OUTCOME_DD;

        a->lastRound = last;
        b->lastRound = last;
        a->roundsPlayed++;
        b->roundsPlayed++;
    }

    historyA[rounds] = '\0';
    historyB[rounds] = '\0';

    printf("Agent A: %s\n", historyA);
    printf("Agent B: %s\n", historyB);
}

int main() {
    const char *input = "Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.";
    const char *input2 = "Agent: x, y: 1, 6. p1=0.30 p2=0.73 p3=0.95. pn1=1.00 pn2=0.45 pn3=0.18 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.";
    Agent a;
    Agent b;

    if (parseAgent(input, &a)) {
        printf("✅ Parsed Agent at (%d,%d): p1=%.2f p2=%.2f p3=%.2f pn1=%.2f pn2=%.2f pn3=%.2f pn4=%.2f rounds=%d\n",
            a.x, a.y, a.p1, a.p2, a.p3, a.pn1, a.pn2, a.pn3, a.pn4, a.roundsPlayed);
    }
    if (parseAgent(input2, &b)) {
        printf("✅ Parsed Agent at (%d,%d): p1=%.2f p2=%.2f p3=%.2f pn1=%.2f pn2=%.2f pn3=%.2f pn4=%.2f rounds=%d\n",
            b.x, b.y, b.p1, b.p2, b.p3, b.pn1, b.pn2, b.pn3, b.pn4, b.roundsPlayed);
    }

    playAndPrintHistory(&a, &b, 100);
}

