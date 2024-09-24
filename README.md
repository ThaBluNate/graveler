# Graveler_x.c: a submission to [ShoddyCast's graveler challenge.](https://youtu.be/M8C8dHQE2Ro)



# Speed
Benchmarks on my ASUS FA707NU-DS74 Laptop (Win11) laptop:

My fastest time on Graveler_B 1.0 was 626.608 seconds

![{C996E4BD-EBA0-40FA-96B6-C7B3A4ECC82C}](https://github.com/user-attachments/assets/79953f3d-ef46-40cb-abfb-fd70cacea818)

On 2.0, however, it was only 178.023 seconds. (Great optimization, me)

![{AA78D6A9-3138-4337-88C0-260CB5571C32}](https://github.com/user-attachments/assets/cf938370-f512-4950-8329-2b60339998ae)



# Implementation (1.0)
The program uses [this implementation](https://lomont.org/papers/2008/Lomont_PRNG_2008.pdf) of WELL-512, a fast and high-quality pRNG function.

The rest of 1.0 mainly consists of a few basic loops. C, of course, because faste.



# Implementation (2.0)
#### In 2.0, instead of using WELL512 modulo 4 and wasting a whole 64 bit result like that, I split the 64 bits into 2-bit pairings (00, 01, 10, 11) for a MUCH faster program with a better-quality randomness spread.
#### In layman's terms, faster dice, and fairer dice*.
###### *as far as I know.



# A vs B
### There are 2 versions of this program, in both 1.0 and 2.0.
Graveler_A rolls until it reaches a number over or equal to 177, and is mainly made to be slightly faster than Version B by eliminating much of the logging code.

Graveler_B does 1 billion rolls, no matter what number comes out of it.
#### Again, version B does not stop if it reaches a number over 177, it will actually fully process 1 Billion rolls...
![{D131262E-3579-4AFB-81F2-D75F7FB36B8B}](https://github.com/user-attachments/assets/8658bcdf-0fe3-4a4c-9688-1f3f5e07f9b8)
###### Screenshot made on earlier version of program, where I was just testing cases like this.
...even if roll 0 already set the max to 232.



# Building & Usage
The program uses only the C standard library, and expects a 64-bit system.

It can be compiled on any basic C99 or C++ compiler that exists, but I used MSVC 2022.

MSVC 2022 building command for binaries (provided in the releses section): `cl /Za /O2 /favor:AMD64 /nologo Graveler_x.c`

To use the program, simply run it. It will start automatically. Seeds are generated randomly.

The other included program, WELLRandSplitterDemo, is an implementation of the RNG without the graveler stuff, so, just a really fast pRNG program. It can be built like all the other C files.
