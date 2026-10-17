#include "msort.h"

#include <algorithm>

// Merges two already-sorted runs arr[left, mid) and arr[mid, right) into
// a single sorted run, using temp as scratch space, then copies the
// result back into arr.
static void merge(int *arr, std::size_t left, std::size_t mid, std::size_t right, int *temp) {
    std::size_t i = left;
    std::size_t j = mid;
    std::size_t k = left;

    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i < mid) {
        temp[k++] = arr[i++];
    }
    while (j < right) {
        temp[k++] = arr[j++];
    }
    for (std::size_t x = left; x < right; x++) {
        arr[x] = temp[x];
    }
}

// Recursively sorts arr[left, right). Below `threshold` elements, falls
// back to std::sort (a serial sort with no further recursive OpenMP
// tasks) to avoid task-scheduling overhead on small subarrays. Above
// threshold, the two recursive halves are spawned as OpenMP tasks so
// they can run concurrently, then a taskwait ensures both halves are
// fully sorted before this level merges them.
static void msort_helper(int *arr, std::size_t left, std::size_t right, std::size_t threshold, int *temp) {
    std::size_t n = right - left;
    if (n <= 1) {
        return;
    }

    if (n < threshold) {
        std::sort(arr + left, arr + right);
        return;
    }

    std::size_t mid = left + n / 2;

    #pragma omp task shared(arr, temp)
    msort_helper(arr, left, mid, threshold, temp);

    #pragma omp task shared(arr, temp)
    msort_helper(arr, mid, right, threshold, temp);

    #pragma omp taskwait

    merge(arr, left, mid, right, temp);
}

void msort(int *arr, const std::size_t n, const std::size_t threshold) {
    if (n <= 1) {
        return;
    }

    int *temp = new int[n];

    #pragma omp parallel
    {
        #pragma omp single
        {
            msort_helper(arr, 0, n, threshold, temp);
        }
    }

    delete[] temp;
}
