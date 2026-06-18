#include <stdlib.h> //malloc
#include <stdio.h> //printf
#include "matrix.h"

#ifdef __linux__
#include <time.h>
#include <unistd.h>
#endif

#define f1024x1024  f, 1024, 1024, float

Matrix_Decl(f1024x1024);
Matrix_Impl_Mul_T(f1024x1024, f1024x1024, f1024x1024);

static unsigned int g_seed;

// Used to seed the generator.           
void fast_srand(int seed);
inline void fast_srand(int seed) {
    g_seed = seed;
}

// Compute a pseudorandom integer.
// Output value in range [0, 32767]
inline int fast_rand(void) {
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}
int fast_rand(void);

void f1024print(Matrix_f1024x1024 a) {
    for(int i = 0; i < 1024; ++i) {
        for(int j = 0; j < 1024; ++j) {
            printf("%f%s", a[i*1024+j], j + 1 < 1024 ? "," : "");
        }
        printf("\n");
    }
    printf("\n");
}

int main(void) {

    float *a = malloc(sizeof(float) * 1024 * 1024);
    float *b = malloc(sizeof(float) * 1024 * 1024);
    float *c = malloc(sizeof(float) * 1024 * 1024);
    printf("..generating random numbers..\n");

    for(int i = 0; i < 1024; ++i) {
        for(int j = 0; j < 1024; ++j) {
            a[i*1024+j] = (float)fast_rand() / 32767;
            b[i*1024+j] = (float)fast_rand() / 32767;
        }
    }

    printf("..calculating..\n");

#ifdef __linux__
    struct timespec t0, tE;
    clock_gettime(CLOCK_MONOTONIC, &t0);
#endif

    matrix_f1024x1024_mul_T_f1024x1024(c, a, b);

#ifdef __linux__
    clock_gettime(CLOCK_MONOTONIC, &tE);
#endif

    f1024print(c);

#ifdef __linux__
    printf("multiplication took %f seconds\n", (double)(tE.tv_sec - t0.tv_sec) + tE.tv_nsec / 1e9 - t0.tv_nsec / 1e9);
#endif

    return 0;
}


