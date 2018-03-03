#include <stdlib.h>
#include <stdio.h>
#include <altivec.h>

#define LOOPMAX  1LL << 20
#define LOOP2    1LL << 8

typedef float v4sf __attribute__ ((vector_size(16)));

int add_mul() {

        v4sf A, B, C, D, E, F, G;
        long long i, z, y;

        long long a = 0;

        A = (v4sf) {20, 2, 9, 100};
        B = (v4sf) {2, 10, 3, 2};
        G = A;

        /* Loop until it overflows */
        for(z = 0; z < LOOPMAX; z++){
            for (y = 0; y < LOOP2; y++)
                C = vec_add(A, G);

            for (y = 0; y < LOOP2; y++)
                D = vec_mul(A, C); /* VSX intruction implemented on Power7 ISA (2.06) */

            for (y = 0; y < LOOP2; y++)
                E = vec_and(A, D); /* VSX intruction implemented on Power7 ISA (2.06) */

            for (y = 0; y < LOOP2; y++)
                F = vec_div(E, B); /* VSX intruction implemented on Power7 ISA (2.06) */

            for (y = 0; y < LOOP2; y++)
                G = vec_xor(F, E); /* VSX intruction implemented on Power7 ISA (2.06) */
        }

        printf("Result vector add:\n");
        for (i = 0; i < 4; i++)
                printf("v[%d]=%f \n", i, G[i]);
        printf("\n");

        return EXIT_SUCCESS;
}

int main(){
    add_mul();

    return 0;
}
