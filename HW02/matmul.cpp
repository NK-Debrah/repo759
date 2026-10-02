#include "matmul.h"

// mmul1: outer loop i (rows of C), middle loop j (columns of C),
// inner loop k (dot product of row i of A with column j of B).
void mmul1(const double* A, const double* B, double* C, const unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            C[i * n + j] = 0.0;
            for (unsigned int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

// mmul2: same as mmul1, but with the two innermost loops swapped:
// (i, j, k) -> (i, k, j).
void mmul2(const double* A, const double* B, double* C, const unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        // C's row i must be zeroed before accumulating over k, since k is no
        // longer the innermost loop (k now runs before j finishes its sweep).
        for (unsigned int j = 0; j < n; j++) {
            C[i * n + j] = 0.0;
        }
        for (unsigned int k = 0; k < n; k++) {
            for (unsigned int j = 0; j < n; j++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

// mmul3: same as mmul1, but the outermost loop (i) becomes the innermost,
// and the other two loops keep their relative order: (i, j, k) -> (j, k, i).
void mmul3(const double* A, const double* B, double* C, const unsigned int n) {
    // Zero out C first, since i is no longer available as an outer loop to
    // pair a single zeroing line with each C[i][j] before accumulation.
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            C[i * n + j] = 0.0;
        }
    }
    for (unsigned int j = 0; j < n; j++) {
        for (unsigned int k = 0; k < n; k++) {
            for (unsigned int i = 0; i < n; i++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

// mmul4: identical loop order to mmul1, but A and B are std::vector<double>.
void mmul4(const std::vector<double>& A, const std::vector<double>& B, double* C, const unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            C[i * n + j] = 0.0;
            for (unsigned int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}
