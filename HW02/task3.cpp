#include "matmul.h"

#include <chrono>
#include <cstdio>
#include <random>
#include <ratio>
#include <vector>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main() {
    const unsigned int n = 1000; // at least 1000 x 1000, per the assignment

    // Store A and B as vectors; mmul1/mmul2/mmul3 read them through
    // .data() (as plain double*), and mmul4 takes the vectors directly.
    std::vector<double> A(static_cast<std::size_t>(n) * n);
    std::vector<double> B(static_cast<std::size_t>(n) * n);

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    for (std::size_t i = 0; i < A.size(); i++) {
        A[i] = dist(gen);
        B[i] = dist(gen);
    }

    double *C1 = new double[static_cast<std::size_t>(n) * n];
    double *C2 = new double[static_cast<std::size_t>(n) * n];
    double *C3 = new double[static_cast<std::size_t>(n) * n];
    double *C4 = new double[static_cast<std::size_t>(n) * n];

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_sec;

    std::printf("%u\n", n);

    start = high_resolution_clock::now();
    mmul1(A.data(), B.data(), C1, n);
    end = high_resolution_clock::now();
    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    std::printf("%f\n", duration_sec.count());
    std::printf("%f\n", C1[static_cast<std::size_t>(n) * n - 1]);

    start = high_resolution_clock::now();
    mmul2(A.data(), B.data(), C2, n);
    end = high_resolution_clock::now();
    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    std::printf("%f\n", duration_sec.count());
    std::printf("%f\n", C2[static_cast<std::size_t>(n) * n - 1]);

    start = high_resolution_clock::now();
    mmul3(A.data(), B.data(), C3, n);
    end = high_resolution_clock::now();
    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    std::printf("%f\n", duration_sec.count());
    std::printf("%f\n", C3[static_cast<std::size_t>(n) * n - 1]);

    start = high_resolution_clock::now();
    mmul4(A, B, C4, n);
    end = high_resolution_clock::now();
    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    std::printf("%f\n", duration_sec.count());
    std::printf("%f\n", C4[static_cast<std::size_t>(n) * n - 1]);

    delete[] C1;
    delete[] C2;
    delete[] C3;
    delete[] C4;

    return 0;
}
