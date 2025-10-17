#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "agent.h"

// Load population for a given cycle from the single file
int loadPopulation(Agent pop[POP_SIZE], int targetCycle) {
    FILE *fp = fopen("populations.bin", "rb");
    if (!fp) {
        perror("Failed to open populations.bin for reading");
        return 0; // failure
    }

    int cycle;
    while (fread(&cycle, sizeof(int), 1, fp) == 1) {
        if (fread(pop, sizeof(Agent), POP_SIZE, fp) != POP_SIZE) {
            fprintf(stderr, "Corrupted data at cycle %d\n", cycle);
            fclose(fp);
            return 0;
        }

        if (cycle == targetCycle) {
            fclose(fp);
            printf("✅ Loaded population from cycle %d\n", targetCycle);
            return 1; // success
        }
    }

    fclose(fp);
    fprintf(stderr, "❌ Cycle %d not found in populations.bin\n", targetCycle);
    return 0; // not found
}

int main() {
    Agent pop[POP_SIZE];

    if (loadPopulation(pop, 8000)) {
        printf("Population at cycle 8000:\n");
        for (int i = 0; i < POP_SIZE; i++) {
            printAgent(&pop[i]);
        }
    }

    return 0;
}