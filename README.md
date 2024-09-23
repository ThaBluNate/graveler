# Graveler_x.c
A submission to [ShoddyCast's graveler challenge.](https://youtu.be/M8C8dHQE2Ro)

My fastest time on Graveler_B was 627.103 seconds, on my ASUS FA707NU-DS74 Laptop (Win11).

![{C996E4BD-EBA0-40FA-96B6-C7B3A4ECC82C}](https://github.com/user-attachments/assets/79953f3d-ef46-40cb-abfb-fd70cacea818)
# Implementation
The program uses [this implementation](https://lomont.org/papers/2008/Lomont_PRNG_2008.pdf) of WELL-512, a fast and high-quality pRNG function.

The rest of this program mainly consists of a few basic loops. C, of course, because faste.
### There are 2 versions of this program.
Graveler_A rolls until it reaches a number over or equal to 177, and is mainly made to be slightly faster than Version B by eliminating much of the logging code.

Graveler_B does 1 billion rolls, no matter what number comes out of it.
#### Again, version B does not stop if it reaches a number over 177, it will actually fully process 1 Billion rolls...
![{D131262E-3579-4AFB-81F2-D75F7FB36B8B}](https://github.com/user-attachments/assets/8658bcdf-0fe3-4a4c-9688-1f3f5e07f9b8)
###### Screenshot made on earlier version of program.
...even if roll 0 already set the max to 232.
# Building & Usage
The program uses only the C standard library, and expects a 64-bit system.

It can be compiled on any basic C99 or C++ compiler that exists, but I used MSVC 2022.

MSVC 2022 building command for binaries (provided in the releses section): `cl /Za /O2 /favor:AMD64 /nologo Graveler_x.c`

To use the program, simply run it. It will start automatically. Seeds are generated randomly.
