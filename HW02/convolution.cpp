#include "convolution.h"

// Returns the "extended" value of the image f at (row, col), handling the
// out-of-bounds padding rule described in the assignment:
//   - if row AND col are both in range:    return the real image value
//   - if exactly one of row/col is in range (an "edge"): return 1
//   - if neither row nor col is in range (a "corner"):   return 0
static float extended_pixel(const float *image, long row, long col, std::size_t n) {
    bool row_in_range = (row >= 0) && (row < static_cast<long>(n));
    bool col_in_range = (col >= 0) && (col < static_cast<long>(n));

    if (row_in_range && col_in_range) {
        return image[static_cast<std::size_t>(row) * n + static_cast<std::size_t>(col)];
    } else if (row_in_range || col_in_range) {
        return 1.0f;
    } else {
        return 0.0f;
    }
}

void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m) {
    // m is guaranteed odd, so this is an exact integer offset: (m - 1) / 2
    long offset = (static_cast<long>(m) - 1) / 2;

    for (std::size_t x = 0; x < n; x++) {
        for (std::size_t y = 0; y < n; y++) {
            float sum = 0.0f;
            for (std::size_t i = 0; i < m; i++) {
                for (std::size_t j = 0; j < m; j++) {
                    long f_row = static_cast<long>(x) + static_cast<long>(i) - offset;
                    long f_col = static_cast<long>(y) + static_cast<long>(j) - offset;
                    sum += mask[i * m + j] * extended_pixel(image, f_row, f_col, n);
                }
            }
            output[x * n + y] = sum;
        }
    }
}
