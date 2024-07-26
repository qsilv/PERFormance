#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>

void heapsort(std::vector<int>& arr);

// Wrapper function to match the signature expected by benchmarkSort
void heapsortWrapper(std::vector<int>& arr, int low, int high);

#endif // HEAPSORT_H
