#include "msort.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <random>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::printf("Usage: %s n t ts\n", argv[0]);
        return 1;
    }

    std::size_t n = static_cast<std::size_t>(std::atoll(argv[1]));
    int t = std::atoi(argv[2]);
    std::size_t ts = static_cast<std::size_t>(std::atoll(argv[3]));
    omp_set_num_threads(t);

    int *arr = new int[n];

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);
    for (std::size_t i = 0; i < n; i++) {
        arr[i] = dist(gen);
    }

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_sec;

    start = high_resolution_clock::now();
    msort(arr, n, ts);
    end = high_resolution_clock::now();

    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    // Print first element, last element, time taken (ms)
    std::printf("%d\n", arr[0]);
    std::printf("%d\n", arr[n - 1]);
    std::printf("%f\n", duration_sec.count());

    delete[] arr;

    return 0;
}
