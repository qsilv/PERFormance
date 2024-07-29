#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>
#include "data_generator.h"
#include "quicksort.h"
#include "heapsort.h"
#include "mergesort.h"

using namespace std;

void benchmarkSort(void(*sortFunc)(vector<int>&, int, int), const string& sortName, const vector<int>& dataset, const string& optimizationLevel, ofstream& outputFile, int arraySize) {
    vector<int> arr = dataset;

    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    outputFile << sortName << ", " << arraySize << ", " << optimizationLevel << ", " << elapsed.count() << " seconds" << endl;
}

void heapsortWrapper(vector<int>& arr, int low, int high) {
    (void) low;
    (void) high;
    heapsort(arr);
}

void benchmark(const string& optimizationLevel, const string& sortName, const string& outputFileName) {
    vector<int> sizes = {10000, 100000, 1000000};

    ofstream outputFile(outputFileName, ios::app);
    if (!outputFile) {
        cerr << "Failed to open output file: " << outputFileName << endl;
        return;
    }

    for (int size : sizes) {
        cout << "Generating random arrays of size " << size << " with " << optimizationLevel << " optimization" << endl;
        vector<int> randomArray = generateRandomArray(size);

        cout << "Benchmarking " << sortName << " with size " << size << " arrays" << endl;
        if (sortName == "Quicksort") {
            benchmarkSort(quicksort, "Quicksort", randomArray, optimizationLevel, outputFile, size);
        } else if (sortName == "Heapsort") {
            benchmarkSort(heapsortWrapper, "Heapsort", randomArray, optimizationLevel, outputFile, size);
        } else if (sortName == "Merge Sort") {
            benchmarkSort(mergesort, "Merge Sort", randomArray, optimizationLevel, outputFile, size);
        }
    }

    outputFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <sort_name> <optimization_level> <output_file>" << endl;
        return 1;
    }

    string sortName = argv[1];
    string optimizationLevel = argv[2];
    string outputFileName = argv[3];

    benchmark(optimizationLevel, sortName, outputFileName);

    return 0;
}
