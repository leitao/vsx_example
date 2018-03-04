#include <stdlib.h>
#include <stdio.h>
#include <altivec.h>

#define LOOPMAX  1LL << 20
#define LOOP2    1LL << 8

typedef float v4sf __attribute__ ((vector_size(16)));

int add_mul(int change) {

        v4sf A, B, C, D, E, F, G;
        long long i, z, y;

        long long a = 0;

        A = (v4sf) {20, 2, 9, change};
        B = (v4sf) {change, 10, 3, 2};
        G = A;
        F = B;

        /* Loop until it overflows */
        for(z = 0; z < LOOPMAX; z++){
            for (y = 0; y < LOOP2; y++)
                C = vec_add(A, F);

            for (y = 0; y < LOOP2; y++)
                D = vec_mul(A, C);

            for (y = 0; y < LOOP2; y++)
                E = vec_and(A, D);

            for (y = 0; y < LOOP2; y++)
                F = vec_or(E, B);

            for (y = 0; y < LOOP2; y++)
                G = vec_xor(F, E);
        }

        return G[3] / E[2];
}

int main(){
    int i;

    /* Forcing the variable to be used, thus the code*/
    int a = 0xffffffff;

    for (i  = 0; i < 1024; i++)
        a ^= add_mul(i);

    printf("Ending with a = %x\n", a);
    return 0;
}
