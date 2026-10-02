#include "convolution.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <ratio>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::printf("Usage: %s n m\n", argv[0]);
        return 1;
    }

    std::size_t n = static_cast<std::size_t>(std::atoll(argv[1]));
    std::size_t m = static_cast<std::size_t>(std::atoll(argv[2]));

    // i) n x n image of random floats in [-10.0, 10.0]
    float *image = new float[n * n];
    // ii) m x m mask of random floats in [-1.0, 1.0]
    float *mask = new float[m * m];
    float *output = new float[n * n];

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> image_dist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> mask_dist(-1.0f, 1.0f);

    for (std::size_t i = 0; i < n * n; i++) {
        image[i] = image_dist(gen);
    }
    for (std::size_t i = 0; i < m * m; i++) {
        mask[i] = mask_dist(gen);
    }

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_sec;

    // iii) Apply the mask to the image
    start = high_resolution_clock::now();
    convolve(image, output, n, mask, m);
    end = high_resolution_clock::now();

    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    // iv) Time taken in milliseconds
    std::printf("%f\n", duration_sec.count());
    // v) First element of the resulting array
    std::printf("%f\n", output[0]);
    // vi) Last element of the resulting array
    std::printf("%f\n", output[n * n - 1]);

    // vii) Deallocate memory
    delete[] image;
    delete[] mask;
    delete[] output;

    return 0;
}
