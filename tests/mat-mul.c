#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "../matrix.h"

#define f3x3    f, 3, 3, float
#define f3x2    f, 3, 2, float
#define f2x3    f, 2, 3, float

Matrix_Decl(f3x3);
Matrix_Decl(f3x2);

Matrix_Impl_Mul(f3x2, f3x3, f3x2);

#define DELTA   1e-6

int main(void) {

    Matrix_f3x3 a = {
        1, 2, 1,
        0, 1, 0,
        2, 3, 4
    };
    Matrix_f3x2 b = {
        2, 5,
        6, 7,
        1, 8
    };
    Matrix_f3x2 x = {
        15, 27,
        6, 7,
        26, 63
    };
    Matrix_f3x2 c = {
        1, 2,
        3, 4,
        5, 6
    };
    matrix_f3x3_mul_f3x2(c, a, b);

    int result = 0;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 2; ++j) {
            printf(" %8.3f", c[i*2+j]);
            if(fabs(c[i*2+j] - x[i*2+j]) > DELTA) {
                printf("<--%f  ", x[i*2+j]);
                result = 1;
            }
        }
        printf("\n");
    }

    return result;
}

