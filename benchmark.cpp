#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include "data_generator.h"
#include "quicksort.h"
#include "heapsort.h"
#include "mergesort.h"
#include <array>
#include <memory>

using namespace std;

// Function to execute a shell command and get the output
string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

// Function to benchmark sorting and collect perf data
void benchmarkSort(void(*sortFunc)(std::vector<int>&, int, int), const string& sortName, const vector<int>& dataset, const string& datasetType, const string& optimizationLevel) {
    vector<int> arr = dataset;
    
    // Start the perf command
    string perfCommand = "perf stat -e branch-misses,cache-misses -x, -o perf_output.txt -- ";
    
    // Benchmark the sort function
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double> elapsed = end - start;
    cout << sortName << " on " << datasetType << " array of size " << arr.size() << " with " << optimizationLevel << " took " << elapsed.count() << " seconds." << endl;
    
    // Read the perf output
    string perfOutput = exec(perfCommand.c_str());
    
    // Parse the perf output
    cout << "Perf Output:\n" << perfOutput << endl;
}

void benchmark(const string& optimizationLevel) {
    vector<int> sizes = {10000, 100000, 1000000};  // Example sizes

    for (int size : sizes) {
        vector<int> randomArray = generateRandomArray(size);
        vector<int> sortedArray = generateSortedArray(size);
        vector<int> reverseSortedArray = generateReverseSortedArray(size);

        benchmarkSort(quicksort, "Quicksort", randomArray, "random", optimizationLevel);
        benchmarkSort(quicksort, "Quicksort", sortedArray, "sorted", optimizationLevel);
        benchmarkSort(quicksort, "Quicksort", reverseSortedArray, "reverse sorted", optimizationLevel);

        benchmarkSort(heapsortWrapper, "Heapsort", randomArray, "random", optimizationLevel);
        benchmarkSort(heapsortWrapper, "Heapsort", sortedArray, "sorted", optimizationLevel);
        benchmarkSort(heapsortWrapper, "Heapsort", reverseSortedArray, "reverse sorted", optimizationLevel);

        benchmarkSort(mergesort, "Merge Sort", randomArray, "random", optimizationLevel);
        benchmarkSort(mergesort, "Merge Sort", sortedArray, "sorted", optimizationLevel);
        benchmarkSort(mergesort, "Merge Sort", reverseSortedArray, "reverse sorted", optimizationLevel);
    }
}

int main() {
    benchmark("O0");
    benchmark("O2");
    benchmark("O3");
    return 0;
}
