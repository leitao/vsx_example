#include <stdlib.h>
#include <stdio.h>
#include <altivec.h>

#define LOOPMAX  1LL << 20
#define LOOP2    1LL << 8

typedef float v4sf __attribute__ ((vector_size(16)));

int add_mul() {

        v4sf A, B, C, D;
        long long i, z, y;

        long long a = 0;

        A = (v4sf) {20, 2, 9, 100};
        B = (v4sf) {2, 10, 3, 2};

        /* Loop until it overflows */
        for(z = 0; z < LOOPMAX; z++){
            a++;
#ifdef VMX
            for (y = 0; y < LOOP2; y++)
                C = vec_add(A, B);
#else

            for (y = 0; y < LOOP2; y++)
                for(i = 0; i < 4; i++)
                    C[i] = A[i] + B[i];
#endif


#ifdef VMX
            for (y = 0; y < LOOP2; y++)
                D = vec_mul(A, B); /* VSX intruction implemented on Power7 ISA (2.06) */
#else /* Fallback to non-vectorized implementation */
            for (y = 0; y < LOOP2; y++)
                for(i = 0; i < 4; i++)
                    D[i] = A[i] * B[i];
#endif

        }

        printf("X: %lx\n", a);

        printf("Result vector add:\n");
        for (i = 0; i < 4; i++)
                printf("v[%d]=%f \n", i,C[i]);
        printf("\n");

        printf("Result vector multiply: \n");
        for (i = 0; i < 4; i++)
                printf("v[%d]=%f \n", i, D[i]);
        printf("\n");

        return EXIT_SUCCESS;
}

int main(){
    add_mul();

    return 0;
}
