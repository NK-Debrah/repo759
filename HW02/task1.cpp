#include "scan.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <ratio>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::printf("Usage: %s n\n", argv[0]);
        return 1;
    }

    // i) Create an array of n random floats between -1.0 and 1.0
    std::size_t n = static_cast<std::size_t>(std::atoll(argv[1]));

    float *arr = new float[n];
    float *output = new float[n];

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    for (std::size_t i = 0; i < n; i++) {
        arr[i] = dist(gen);
    }

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_sec;

    // ii) Scan the array
    start = high_resolution_clock::now();
    scan(arr, output, n);
    end = high_resolution_clock::now();

    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    // iii) Time taken in milliseconds
    std::printf("%f\n", duration_sec.count());
    // iv) First element of the output array
    std::printf("%f\n", output[0]);
    // v) Last element of the output array
    std::printf("%f\n", output[n - 1]);

    // vi) Deallocate memory
    delete[] arr;
    delete[] output;

    return 0;
}
