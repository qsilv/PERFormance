#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include "data_generator.h"
#include "quicksort.h"
#include "heapsort.h"
#include "mergesort.h"

using namespace std;

void benchmarkSort(void(*sortFunc)(vector<int>&, int, int), const string& sortName, const vector<int>& dataset, const string& optimizationLevel) {
    vector<int> arr = dataset;

    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
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
        cout << "Generating random arrays of size " << size << " with " << optimizationLevel << " optimization" << endl;
        vector<int> randomArray = generateRandomArray(size);

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

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <sort_name> <optimization_level>" << endl;
        return 1;
    }

    string sortName = argv[1];
    string optimizationLevel = argv[2];

    benchmark(optimizationLevel, sortName);

    return 0;
}
