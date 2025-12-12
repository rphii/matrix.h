#ifndef MATRIX_H

#include <assert.h>
#include <string.h>

#define Matrix_Type(A, S2, S1)          \
    Matrix_##A##S2##x##S1
#define Matrix_Size(S2, S1)             \
    ((S1)*(S2))

/* typedef declaration */
#define  Matrix_Decl(X)                 \
        _Matrix_Decl(X)
#define _Matrix_Decl(A, S2, S1, T)      \
    typedef T Matrix_##A##S2##x##S1[Matrix_Size(S2, S1)]

/* {{{ dimension info graph
 *   A : S2(rows) x S1(cols)
 *   B : R2(rows) x R1(cols)
 *   C : Q2(rows) x Q1(cols)
 * }}} */

/* {{{ matrix_mul : out = a * b */
#define  Matrix_Decl_Mul(Z, X, Y) \
        _Matrix_Decl_Mul(Z, X, Y)
#define _Matrix_Decl_Mul(C, Q2, Q1, W, A, S2, S1, T, B, R2, R1, U) \
    static_assert(Q1 == R1, "Q1:R1 dimension mismatch"); \
    static_assert(Q2 == S2, "Q2:S2 dimension mismatch"); \
    static_assert(S1 == R2, "S1:R2 dimension mismatch"); \
    void matrix_##A##S2##x##S1##_mul_##B##R2##x##R1( \
            Matrix_Type(C,Q2,Q1), \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(B,R2,R1));
#define  Matrix_Impl_Mul(Z, X, Y)   \
        _Matrix_Impl_Mul(Z, X, Y)
#define _Matrix_Impl_Mul(C, Q2, Q1, W, A, S2, S1, T, B, R2, R1, U) \
    static_assert(Q1 == R1, "Q1:R1 dimension mismatch"); \
    static_assert(Q2 == S2, "Q2:S2 dimension mismatch"); \
    static_assert(S1 == R2, "S1:R2 dimension mismatch"); \
    void matrix_##A##S2##x##S1##_mul_##B##R2##x##R1( \
            Matrix_Type(C,Q2,Q1) out, \
            Matrix_Type(A,S2,S1) a, \
            Matrix_Type(B,R2,R1) b) { \
        for(int q2 = 0; q2 < Q2; ++q2) { \
            for(int q1 = 0; q1 < Q1; ++q1) { \
                T tmp = {0}; \
                for(int s1 = 0; s1 < S1; ++s1) { \
                    tmp += a[q2*S1+s1] * b[s1*R1+q1]; \
                } \
                out[q2*Q1+q1] = tmp; \
            } \
        } \
    } /*}}}*/

/* {{{ matrix_mul_T : out = a * b.T */
#define  Matrix_Decl_Mul_T(Z, X, Y) \
        _Matrix_Decl_Mul_T(Z, X, Y)
#define _Matrix_Decl_Mul_T(C, Q2, Q1, W, A, S2, S1, T, B, R2, R1, U) \
    static_assert(Q1 == R2, "Q1:R2 dimension mismatch"); \
    static_assert(Q2 == S2, "Q2:S2 dimension mismatch"); \
    static_assert(S1 == R1, "S1:R1 dimension mismatch"); \
    void matrix_##A##S2##x##S1##_mul_T_##B##R2##x##R1( \
            Matrix_Type(C,Q2,Q1), \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(B,R2,R1));
#define  Matrix_Impl_Mul_T(Z, X, Y)   \
        _Matrix_Impl_Mul_T(Z, X, Y)
#define _Matrix_Impl_Mul_T(C, Q2, Q1, W, A, S2, S1, T, B, R2, R1, U) \
    static_assert(Q1 == R2, "Q1:R2 dimension mismatch"); \
    static_assert(Q2 == S2, "Q2:S2 dimension mismatch"); \
    static_assert(S1 == R1, "S1:R1 dimension mismatch"); \
    void matrix_##A##S2##x##S1##_mul_T_##B##R2##x##R1( \
            Matrix_Type(C,Q2,Q1) out, \
            Matrix_Type(A,S2,S1) a, \
            Matrix_Type(B,R2,R1) b) { \
        for(int q2 = 0; q2 < Q2; ++q2) { \
            for(int q1 = 0; q1 < Q1; ++q1) { \
                T tmp = {0}; \
                for(int s1 = 0; s1 < S1; ++s1) { \
                    tmp += a[q2*S1+s1] * b[q1*R1+s1]; \
                } \
                out[q2*Q1+q1] = tmp; \
            } \
        } \
    } /*}}}*/

/* {{{ matrix_mul_T_add : out += a * b.T */
#define  Matrix_Decl_Mul_T_Add(Z, X, Y) \
        _Matrix_Decl_Mul_T_Add(Z, X, Y)
#define _Matrix_Decl_Mul_T_Add(C, Q2, Q1, W, A, S2, S1, T, B, R2, R1, U) \
    static_assert(Q1 == R2, "Q1:R2 dimension mismatch"); \
    static_assert(Q2 == S2, "Q2:S2 dimension mismatch"); \
    static_assert(S1 == R1, "S1:R1 dimension mismatch"); \
    void matrix_##A##S2##x##S1##_mul_T_add_##B##R2##x##R1( \
            Matrix_Type(C,Q2,Q1), \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(B,R2,R1));
#define  Matrix_Impl_Mul_T_Add(Z, X, Y)   \
        _Matrix_Impl_Mul_T_Add(Z, X, Y)
#define _Matrix_Impl_Mul_T_Add(C, Q2, Q1, W, A, S2, S1, T, B, R2, R1, U) \
    static_assert(Q1 == R2, "Q1:R2 dimension mismatch"); \
    static_assert(Q2 == S2, "R2:S2 dimension mismatch"); \
    static_assert(S1 == R1, "S1:R1 dimension mismatch"); \
    void matrix_##A##S2##x##S1##_mul_T_add_##B##R2##x##R1( \
            Matrix_Type(C,Q2,Q1) out, \
            Matrix_Type(A,S2,S1) a, \
            Matrix_Type(B,R2,R1) b) { \
        for(int q2 = 0; q2 < Q2; ++q2) { \
            for(int q1 = 0; q1 < Q1; ++q1) { \
                T tmp = {0}; \
                for(int s1 = 0; s1 < S1; ++s1) { \
                    tmp += a[q2*S1+s1] * b[q1*R1+s1]; \
                } \
                out[q2*Q1+q1] += tmp; \
            } \
        } \
    } /*}}}*/

/* {{{ matrix_mul_T_scale : out = a * b.T * scale */
#define  Matrix_Decl_Mul_T_Scale(Z, X, Y) \
        _Matrix_Decl_Mul_T_Scale(Z, X, Y)
#define _Matrix_Decl_Mul_T_Scale(C, Q2, Q1, W, A, S2, S1, T, B, R2, R1, U) \
    static_assert(Q1 == R2, "Q1:R2 dimension mismatch"); \
    static_assert(Q2 == S2, "Q2:S2 dimension mismatch"); \
    static_assert(S1 == R1, "S1:R1 dimension mismatch"); \
    void matrix_##A##S2##x##S1##_mul_T_scale_##B##R2##x##R1( \
            Matrix_Type(C,Q2,Q1), \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(B,R2,R1), \
            T scale);
#define  Matrix_Impl_Mul_T_Scale(Z, X, Y)   \
        _Matrix_Impl_Mul_T_Scale(Z, X, Y)
#define _Matrix_Impl_Mul_T_Scale(C, Q2, Q1, W, A, S2, S1, T, B, R2, R1, U) \
    static_assert(Q1 == R2, "Q1:R2 dimension mismatch"); \
    static_assert(Q2 == S2, "Q2:S2 dimension mismatch"); \
    static_assert(S1 == R1, "S1:R1 dimension mismatch"); \
    void matrix_##A##S2##x##S1##_mul_T_scale_##B##R2##x##R1( \
            Matrix_Type(C,Q2,Q1) out, \
            Matrix_Type(A,S2,S1) a, \
            Matrix_Type(B,R2,R1) b, \
            T scale) { \
        for(int q2 = 0; q2 < Q2; ++q2) { \
            for(int q1 = 0; q1 < Q1; ++q1) { \
                T tmp = {0}; \
                for(int s1 = 0; s1 < S1; ++s1) { \
                    tmp += a[q2*S1+s1] * b[q1*R1+s1]; \
                } \
                out[q2*Q1+q1] = tmp * scale; \
            } \
        } \
    } /*}}}*/

/* {{{ matrix_add : out = a + b */
#define  Matrix_Decl_Add(X) \
        _Matrix_Decl_Add(X)
#define _Matrix_Decl_Add(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_add( \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(A,S2,S1));
#define  Matrix_Impl_Add(X)   \
        _Matrix_Impl_Add(X)
#define _Matrix_Impl_Add(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_add( \
            Matrix_Type(A,S2,S1) out, \
            Matrix_Type(A,S2,S1) a, \
            Matrix_Type(A,S2,S1) b) { \
        for(int s2 = 0; s2 < S2; ++s2) { \
            for(int s1 = 0; s1 < S1; ++s1) { \
                out[s2*S1+s1] = a[s2*S1+s1] + b[s2*S1+s1]; \
            } \
        } \
    } /*}}}*/

/* {{{ matrix_add_inplace : out += a */
#define  Matrix_Decl_Add_Inplace(X) \
        _Matrix_Decl_Add_Inplace(X)
#define _Matrix_Decl_Add_Inplace(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_add_inplace( \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(A,S2,S1));
#define  Matrix_Impl_Add_Inplace(X)   \
        _Matrix_Impl_Add_Inplace(X)
#define _Matrix_Impl_Add_Inplace(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_add_inplace( \
            Matrix_Type(A,S2,S1) out, \
            Matrix_Type(A,S2,S1) a) { \
        for(int s2 = 0; s2 < S2; ++s2) { \
            for(int s1 = 0; s1 < S1; ++s1) { \
                out[s2*S1+s1] += a[s2*S1+s1]; \
            } \
        } \
    } /*}}}*/

/* {{{ matrix_sub : out = a - b */
#define  Matrix_Decl_Sub(X) \
        _Matrix_Decl_Sub(X)
#define _Matrix_Decl_Sub(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_sub( \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(A,S2,S1));
#define  Matrix_Impl_Sub(X)   \
        _Matrix_Impl_Sub(X)
#define _Matrix_Impl_Sub(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_sub( \
            Matrix_Type(A,S2,S1) out, \
            Matrix_Type(A,S2,S1) a, \
            Matrix_Type(A,S2,S1) b) { \
        for(int s2 = 0; s2 < S2; ++s2) { \
            for(int s1 = 0; s1 < S1; ++s1) { \
                out[s2*S1+s1] = a[s2*S1+s1] - b[s2*S1+s1]; \
            } \
        } \
    } /*}}}*/

/* {{{ matrix_sub_inplace : out -= a */
#define  Matrix_Decl_Sub_Inplace(X) \
        _Matrix_Decl_Sub_Inplace(X)
#define _Matrix_Decl_Sub_Inplace(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_sub_inplace( \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(A,S2,S1));
#define  Matrix_Impl_Sub_Inplace(X)   \
        _Matrix_Impl_Sub_Inplace(X)
#define _Matrix_Impl_Sub_Inplace(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_sub_inplace( \
            Matrix_Type(A,S2,S1) out, \
            Matrix_Type(A,S2,S1) a) { \
        for(int s2 = 0; s2 < S2; ++s2) { \
            for(int s1 = 0; s1 < S1; ++s1) { \
                out[s2*S1+s1] -= a[s2*S1+s1]; \
            } \
        } \
    } /*}}}*/

/* {{{ matrix_cholesky_lower : decomposes a matrix into lower triangular form using cholesky decomposition
 * return zero    : success
 * return nonzero : matrix is not positive semi-definite
 * */
#define  Matrix_Decl_Cholesky_Lower(X) \
        _Matrix_Decl_Cholesky_Lower(X)
#define _Matrix_Decl_Cholesky_Lower(A, S2, S1, T) \
    static_assert(S1 == S2, "S1:S2 require square matrix"); \
    int matrix_##A##S2##x##S1##_cholesky_lower( \
            Matrix_Type(A,S2,S1));
#define  Matrix_Impl_Cholesky_Lower(X, SQRT)   \
        _Matrix_Impl_Cholesky_Lower(X, SQRT)
#define _Matrix_Impl_Cholesky_Lower(A, S2, S1, T, SQRT) \
    static_assert(S1 == S2, "S1:S2 require square matrix"); \
    int matrix_##A##S2##x##S1##_cholesky_lower( \
            Matrix_Type(A,S2,S1) a) { \
        T el_div; \
        for(int s2 = 0; s2 < S2; ++s2) { \
            for(int s1 = 0; s1 < S1; ++s1) { \
                T sum = a[s2*S1+s1]; \
                for(int i = 0; i < s2; ++i) { \
                    sum -= a[s2*S1+i] * a[s1*S2+i]; \
                } \
                if(s1 == s2) { \
                    if(sum <= 0) return 1; \
                    T el = SQRT(sum); \
                    a[s2*S1+s2] = el; \
                    el_div = ((T)1) / el; \
                } else { \
                    a[s1*S2+s2] = sum * el_div; \
                } \
            } \
        } \
        /* zero top right corner */ \
        for(int s2 = 0; s2 < S2; ++s2) { \
            for(int s1 = s2 + 1; s1 < S1; ++s1) { \
                a[s2*S1+s1] = 0; \
            } \
        } \
        return 0; \
    } /*}}}*/

/* {{{ matrix_invert_lower : inverts a lower triangular matrix */
#define  Matrix_Decl_Invert_Lower(X) \
        _Matrix_Decl_Invert_Lower(X)
#define _Matrix_Decl_Invert_Lower(A, S2, S1, T) \
    static_assert(S1 == S2, "S1:S2 require square matrix"); \
    void matrix_##A##S2##x##S1##_invert_lower( \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(A,S2,S1));
#define  Matrix_Impl_Invert_Lower(X)   \
        _Matrix_Impl_Invert_Lower(X)
#define _Matrix_Impl_Invert_Lower(A, S2, S1, T) \
    static_assert(S1 == S2, "S1:S2 require square matrix"); \
    void matrix_##A##S2##x##S1##_invert_lower( \
            Matrix_Type(A,S2,S1) out, \
            Matrix_Type(A,S2,S1) a) { \
        for(int s2 = 0; s2 < S2; ++s2) { \
            T el = a[s2*S1+s2]; \
            for(int s1 = 0; s1 <= s2; ++s1) { \
                T sum = (s2 == s1) ? (T)1 : (T)0; \
                for(int i = s2 - 1; i >= s1; --i) { \
                    sum -= a[s2*S1+i] * out[s1*S2+i]; \
                } \
                out[s1*S2+s2] = sum / el; \
            } \
        } \
        /* solve the system */ \
        for(int s2 = S2 - 1; s2 >= 0; --s2) { \
            T el = a[s2*S1+s2]; \
            for(int s1 = 0; s1 <= s2; ++s1) { \
                T sum = (s2<s1) ? 0 : out[s1*S2+s2]; \
                for(int i = s2 + 1; i < S2; ++i) { \
                    sum -= a[i*S1+s2] * out[s1*S2+i]; \
                } \
                out[s2*S1+s1] = out[s1*S2+s2] = sum / el; \
            } \
        } \
    } /*}}}*/

/* {{{ matrix_transpose : out = a.T */
#define  Matrix_Decl_Transpose(X) \
        _Matrix_Decl_Transpose(X)
#define _Matrix_Decl_Transpose(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_transpose( \
            Matrix_Type(A,S1,S2), \
            Matrix_Type(A,S2,S1));
#define  Matrix_Impl_Transpose(X)   \
        _Matrix_Impl_Transpose(X)
#define _Matrix_Impl_Transpose(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_transpose( \
            Matrix_Type(A,S1,S2) out, \
            Matrix_Type(A,S2,S1) a) { \
        for(int s2 = 0; s2 < S2; ++s2) { \
            for(int s1 = 0; s1 < S1; ++s1) { \
                out[s1*S2+s2] = a[s2*S1+s1]; \
            } \
        } \
    } /*}}}*/

/* {{{ matrix_identity : out = a.T */
#define  Matrix_Decl_Identity(X) \
        _Matrix_Decl_Identity(X)
#define _Matrix_Decl_Identity(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_identity( \
            Matrix_Type(A,S2,S1));
#define  Matrix_Impl_Identity(X)   \
        _Matrix_Impl_Identity(X)
#define _Matrix_Impl_Identity(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_identity( \
            Matrix_Type(A,S2,S1) a) { \
        memset(a, 0, sizeof(T) * S1 * S2); \
        int end = (S2 < S1) ? S2 : S1; \
        for(int i = 0; i < end; ++i) { \
            a[i*S1+i] = 1; \
        } \
    } /*}}}*/

/* {{{ matrix_copy : out = a */
#define  Matrix_Decl_Copy(X) \
        _Matrix_Decl_Copy(X)
#define _Matrix_Decl_Copy(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_copy( \
            Matrix_Type(A,S2,S1), \
            Matrix_Type(A,S2,S1));
#define  Matrix_Impl_Copy(X)   \
        _Matrix_Impl_Copy(X)
#define _Matrix_Impl_Copy(A, S2, S1, T) \
    void matrix_##A##S2##x##S1##_copy( \
            Matrix_Type(A,S2,S1) out, \
            Matrix_Type(A,S2,S1) a) { \
        memcpy(out, a, sizeof(T) * S1 * S2); \
    } /*}}}*/

#define MATRIX_H
#endif // MATRIX_H

