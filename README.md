# matrix.h

Matrix prototype header targeted for low-memory systems

## [Example](example.c)

_gcc example.c && ./a.out_

```c
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
```

Test run:

```c
$ gcc example.c && ./a.out 
    1.000    5.000
    2.000    6.000
    3.000    7.000
    4.000    8.000
```

## [Example 1024](example1024.c)

_gcc example1024.c -O3 -march=native && ./a.out_

## Available feature set

- `T    matrix_XXX_sum ( A )` retval += A\[..\]\[..\] *(all indices summed up)*
- `void matrix_XXX_mul_YYY ( out, A, B )` out = A x B
- `void matrix_XXX_mul_T_YYY ( out, A, B )` out = A x B.T
- `void matrix_XXX_mul_T_add_YYY ( out, A, B )` out += A x B.T
- `void matrix_XXX_mul_T_scale_YYY ( out, A, B, scale )` out = A x B.T x scale
- `void matrix_XXX_add ( out, A, B )` out = A + B
- `void matrix_XXX_add_inplace ( out, A )` out += A
- `void matrix_XXX_sub ( out, A, B )` out = A - B
- `void matrix_XXX_sub_inplace ( out, A )` out -= A
- `int  matrix_XXX_cholesky_lower ( A ) -> int` A = cholesky\_lower(A)
- `void matrix_XXX_invert_lower ( A )` A = invert\_lower(A)
- `void matrix_XXX_transpose ( out, A )` out = A.T
- `void matrix_XXX_identity ( A )` A = identity
- `void matrix_XXX_copy ( out, A )` out = A

## Implementation details

1. `XXX` -> substituted with your type name for A _(e.g. `f2x4`)_
2. `YYY` -> substituted with your type name for B _(e.g. `f2x4`)_
3. Output is always the first argument, such that `C = A * b` == `matrix_f2x4_mul_f4x2(C, A, B)`
4. The "helper definition": `f, 2, 4, float` has implications:
    - `f` -> required for unique identification for the type and function names (e.g. `Matrix_` **`f`** `2x4`)
    - `2, 4` -> required for the size (e.g. `Matrix_f` **`2x4`**)
    - `float` -> the underlying matrix type
5. Keep `out` value different from `A` and `B` (it is unsafe to assume a function does not modify `A` or `B` if either is the same variable as `out`
6. If `A` is the only argument, the operation is in-place _(cholesky, invert)_
7. Dimension verification happens at compile-time, through `static_assert` in `_Decl` and `_Impl`, but **!! NEVER !!** during runtime on your input/output variables, as the matrix is a simple 1-dimensional array and nothing more
8. Implementations always use ONE type for everything

