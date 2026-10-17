#include "convolution.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <random>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::printf("Usage: %s n t\n", argv[0]);
        return 1;
    }

    std::size_t n = static_cast<std::size_t>(std::atoll(argv[1]));
    int t = std::atoi(argv[2]);
    const std::size_t m = 3;
    omp_set_num_threads(t);

    float *image = new float[n * n];
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

    start = high_resolution_clock::now();
    convolve(image, output, n, mask, m);
    end = high_resolution_clock::now();

    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    // Print first element, last element, time taken (ms)
    std::printf("%f\n", output[0]);
    std::printf("%f\n", output[n * n - 1]);
    std::printf("%f\n", duration_sec.count());

    delete[] image;
    delete[] mask;
    delete[] output;

    return 0;
}
