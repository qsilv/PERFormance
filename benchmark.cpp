#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <array>
#include <memory>
#include "data_generator.h"
#include "quicksort.h"
#include "heapsort.h"
#include "mergesort.h"

using namespace std;

void benchmarkSort(void(*sortFunc)(vector<int>&, int, int), const string& sortName, const vector<int>& dataset, const string& optimizationLevel) {
    vector<int> arr = dataset;
    
    // Benchmark the sort function

    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << sortName << " on " << datasetType << " array of size " << arr.size() << " with " << optimizationLevel << " took " << elapsed.count() << " seconds." << endl;
}

// Wrapper function for Heapsort to match the signature expected by benchmarkSort
void heapsortWrapper(vector<int>& arr, int low, int high) {
    (void) low;  // Unused parameter
    (void) high; // Unused parameter
    heapsort(arr);
    cout << sortName << " on random array of size " << arr.size() << " with " << optimizationLevel << " took " << elapsed.count() << " seconds." << endl;
}

void heapsortWrapper(vector<int>& arr, int low, int high) {
    (void) low;
    (void) high;
    heapsort(arr);
}

void benchmark(const string& optimizationLevel, const string& sortName) {
    vector<int> sizes = {10000, 100000, 1000000};

    for (int size : sizes) {
        cout << "Generating arrays of size " << size << endl;
        cout << "Generating random arrays of size " << size << " with " << optimizationLevel << " optimization" << endl;
        vector<int> randomArray = generateRandomArray(size);
        vector<int> sortedArray = generateSortedArray(size);
        vector<int> reverseSortedArray = generateReverseSortedArray(size);

        cout << "Benchmarking Quicksort with size " << size << " arrays" << endl;
        benchmarkSort(quicksort, "Quicksort", randomArray, "random", optimizationLevel);
        benchmarkSort(quicksort, "Quicksort", sortedArray, "sorted", optimizationLevel);
        benchmarkSort(quicksort, "Quicksort", reverseSortedArray, "reverse sorted", optimizationLevel);

        cout << "Benchmarking Heapsort with size " << size << " arrays" << endl;
        benchmarkSort(heapsortWrapper, "Heapsort", randomArray, "random", optimizationLevel);
        benchmarkSort(heapsortWrapper, "Heapsort", sortedArray, "sorted", optimizationLevel);
        benchmarkSort(heapsortWrapper, "Heapsort", reverseSortedArray, "reverse sorted", optimizationLevel);

        cout << "Benchmarking Merge Sort with size " << size << " arrays" << endl;
        benchmarkSort(mergesort, "Merge Sort", randomArray, "random", optimizationLevel);
        benchmarkSort(mergesort, "Merge Sort", sortedArray, "sorted", optimizationLevel);
        benchmarkSort(mergesort, "Merge Sort", reverseSortedArray, "reverse sorted", optimizationLevel);
    }
}

int main() {
    cout << "Starting benchmarks with -O0 optimization" << endl;
    benchmark("O0");
    cout << "Finished benchmarks with -O0 optimization" << endl;

    cout << "Starting benchmarks with -O2 optimization" << endl;
    benchmark("O2");
    cout << "Finished benchmarks with -O2 optimization" << endl;

    cout << "Starting benchmarks with -O3 optimization" << endl;
    benchmark("O3");
    cout << "Finished benchmarks with -O3 optimization" << endl;

    return 0;

        cout << "Benchmarking " << sortName << " with size " << size << " arrays" << endl;
        if (sortName == "Quicksort") {
            benchmarkSort(quicksort, "Quicksort", randomArray, optimizationLevel);
        } else if (sortName == "Heapsort") {
            benchmarkSort(heapsortWrapper, "Heapsort", randomArray, optimizationLevel);
        } else if (sortName == "Merge Sort") {
            benchmarkSort(mergesort, "Merge Sort", randomArray, optimizationLevel);
        }
    }
}
