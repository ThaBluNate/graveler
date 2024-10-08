#include <stdio.h>     // printf()
#include <stdint.h>   // uint64_t
#include <time.h>    // time(), clock_t, clock(), CLOCKS_PER_SEC
#include <stdlib.h> // rand() [used for seed generation]

// Used by WELL512
uint64_t state[16];
unsigned int index = 0;
// Used for program
unsigned int max = 0;
uint64_t rolls = 0;
uint64_t random;
clock_t startTimer;

uint64_t WELLrand() { //Thank you, https://lomont.org/papers/2008/Lomont_PRNG_2008.pdf, I will be taking that.
    uint64_t a, b, c, d;
    a = state[index];
    c = state[(index+13)&15];
    b = a^c^(a<<16)^(c<<15);
    c = state[(index+9)&15];
    c ^= (c>>11);
    a = state[index] = b^c;
    d = a^((a<<5)&0xDA442D24ULL);
    index = (index + 15)&15;
    a = state[index];
    state[index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
    return state[index];
}

void main(){
    printf("Generating RNG seed... <");
    srand((unsigned int)time(NULL));//Generate the seed for the WELL512 with a few rand() calls.
    for (int i = 0; i < 16; i++) {  //Generates warnings. I don't care.
        state[i] =  ((rand()&65535) << 48) |
                    ((rand()&65535) << 32) |
                    ((rand()&65535) << 16) |
                    ( rand()&65535       ) ;
        printf("%08llx", state[i]);
    }
    printf(">\n");

    printf("Started program! Currently processing your rolls.\n");
    startTimer = clock();
    while(max <= 177){
        unsigned int current = 0;
        for (unsigned int i = 0; i < 231; ++i) {
            if (i % 64 == 0) {random=WELLrand();}
            if (((random >> (i % 32)*2) & 3) == 0) {++current;} //Trust me, this is 1 in 4
        }
        if (current > max) {printf("New max reached! %u\n", (max = current));}
        ++rolls;
    }
    printf("Done! Processed %llu rolls in %f seconds\n", rolls, (double)(clock() - startTimer)/CLOCKS_PER_SEC);
    printf("Final max = %u", max);
}