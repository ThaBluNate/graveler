#include <stdio.h>     // printf()
#include <stdint.h>   // uint64_t
#include <time.h>    // time(), clock_t, clock(), CLOCKS_PER_SEC
#include <stdlib.h> // rand() [used for seed generation]

// Used by WELL512
unsigned long state[16];
unsigned int index = 0;
// Used for program
unsigned int max = 0;
uint64_t rolls = 0;
// Used by program for extra output, including what roll held the maximum, percentage of 1B complete, and the timer.
uint64_t rollMax = 0;
clock_t startTimer;
unsigned int percentComplete=0;

unsigned int goodrand() { //Thank you, https://lomont.org/papers/2008/Lomont_PRNG_2008.pdf, I will be taking that.
    unsigned long a, b, c, d;
    a = state[index];
    c = state[(index+13)&15];
    b = a^c^(a<<16)^(c<<15);
    c = state[(index+9)&15];
    c ^= (c>>11);
    a = state[index] = b^c;
    d = a^((a<<5)&0xDA442D24UL);
    index = (index + 15)&15;
    a = state[index];
    state[index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
    return state[index]%4;
}

void main(){
    printf("Generating RNG seed... <");
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 16; i++) {state[i] = (unsigned long)rand(); printf("%u", state[i]);}
    printf(">\n");
    printf("Started program! Currently processing 1B rolls.\n");
    startTimer = clock();
    while (rolls < 1000000000) { // 1 Billion!
        unsigned int current = 0;
        for (unsigned int i = 0; i < 232; ++i) {
            if (goodrand() == 0) {
                ++current;
            }
        }
        if (current > max) {
            printf("New max reached! %u (was %u)\n", current, max);
            max = current;
            rollMax = rolls;
        }
        ++rolls;
        if (rolls%10000000 == 0) {
            ++percentComplete;
            printf("Finished processing 10M rolls, %u%c complete\n", percentComplete, '%');
        }
    }
    printf("Done! Processed 1B rolls in %f seconds\n", (double)(clock() - startTimer)/CLOCKS_PER_SEC);
    printf("Max was acheived on roll %u, with max = %u", rollMax, max);
}