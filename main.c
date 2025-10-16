#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "agent.h"
#include "population.h"
#include "utils.h"



int main(void) {

    FILE *fp = fopen("avgPayoff.csv", "w");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    // Optional: write header
    fprintf(fp, "cycle,avgPayoff\n");

    srand((unsigned)time(NULL));

    Agent population[POP_SIZE];

    // --- Initialize the grid with random agents ---
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int index = i * GRID_SIZE + j;
            population[index] = makeRandomAgent(i, j);
        }
    }

    // --- Simulation loop ---
    for (int c = 0; c < CYCLE; c++) {
        matchPopulation(population);

        // Compute average payoff
        avgPopPayoff = computeAvgPopPayoff(population);
        // Write to CSV
        fprintf(fp, "%d,%.4f\n", c, avgPopPayoff);

        printf("Average population payoff after cycle %d: %.2f\n", c, avgPopPayoff);

        // --- Selection and replacement ---
        int size = 0;
        int *lst = findUnderplayed(population, &size);
        if (lst == NULL || size == 0) {
            printf("No underplayed agents found in cycle %d.\n", c);
            continue;
        }

        Agent *pool = collectUnderplayedAgents(population, lst, size);
        if (pool == NULL) {
            free(lst);
            continue;
        }

        shufflePool(pool, size);
        rematchPool(pool, size);
        refillPopulation(population, pool, lst, size);

        free(pool);
        free(lst);

        regenerate(population);
        mutate(population);
    }

    printf("\nPrinting some resulting agents:");
    for(int i = 0; i < 5; i++)  {
        printAgent(&population[i]);
    }
    
    fclose(fp);
    printf("CSV saved to avgPayoff.csv\n");
    return 0;
}