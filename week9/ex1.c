#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    int frames = 10; // Also 50 and 100 can be used

    printf("Simulation of paging system using Ageing algorithm with %d frames\n", frames);

    int *pages = malloc(frames * sizeof(int));
    memset(pages, 0, frames);
    unsigned char *age = malloc(frames * sizeof(unsigned char));
    memset(age, 0, frames);

    FILE* file = fopen("Lab 09 input.txt", "r");

    int hits = 0;
    int misses = 0;
    int current;

    while(fscanf(file, "%d", &current) != EOF) {
        int p = -1;

        for (int i = 0; i < frames; ++i)
            if (current == pages[i]) {
                p = i;
            }

        if (p == -1) {
            int i_min = 0;

            for (int i = 0; i < frames; ++i)
                if (age[i] < age[i_min]) {
                    i_min = i;
                }

            pages[i_min] = current;
            age[i_min] = 1 << 7;

            misses++;
        } else {
            age[p] >>= 1;
            age[p] |= 1<<7;

            hits++;
        }
    }

    printf("Hits: %d\nMisses: %d\n", hits, misses);
    printf("Hit/Miss ratio: %f\n", (double)hits / misses);

    return 0;
}

