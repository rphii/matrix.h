#include <stdio.h> //printf
#include "matrix.h"

/* Create a helper define, specifying the type and dimension */
#define f2x4    f, 2, 4, float
#define f4x2    f, 4, 2, float

/* Declare the type */
Matrix_Decl(f2x4);
Matrix_Decl(f4x2);

/* Declare a function */
Matrix_Decl_Transpose(f2x4)
Matrix_Decl_Transpose(f4x2)

/* Implement a function */
Matrix_Impl_Transpose(f2x4)
Matrix_Impl_Transpose(f4x2)

/* Test */
int main(void) {
    Matrix_f2x4 a = {
        1, 2, 3, 4,
        5, 6, 7, 8
    };
    Matrix_f4x2 aT;

    matrix_f2x4_transpose(aT, a);

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 2; ++j) {
            printf(" %8.3f", aT[i*2+j]);
        }
        printf("\n");
    }
    return 0;
}

