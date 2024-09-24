#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint64_t rolls = 0;
uint64_t state[16];
uint64_t random;
unsigned int index = 0;

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

    while(1){   //Demo part, will continuously make random.
        if(rolls % 64 == 0){
            random=WELLrand();
            printf("\nGenerating new random...\n");
        }
        printf("%llx", ((random >> (rolls % 32)*2) & 3));
        ++rolls;
    }
}