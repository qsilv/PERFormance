#include <iostream>
#include <vector>
#include <algorithm> // for std::is_sorted
#include "data_generator.h"
#include "quicksort.h"
#include "heapsort.h"
#include "mergesort.h"

using namespace std;

// Function to test a sorting algorithm
void testSort(void(*sortFunc)(std::vector<int>&, int, int), const string& sortName) {
    vector<int> sizes = {10, 100, 1000, 10000};  // Example sizes

    for (int size : sizes) {
        vector<int> randomArray = generateRandomArray(size);
        vector<int> sortedArray = generateSortedArray(size);
        vector<int> reverseSortedArray = generateReverseSortedArray(size);

        // Test random array
        vector<int> arr = randomArray;
        sortFunc(arr, 0, arr.size() - 1);
        if (is_sorted(arr.begin(), arr.end())) {
            cout << sortName << " successfully sorted a random array of size " << size << "." << endl;
        } else {
            cout << sortName << " failed to sort a random array of size " << size << "." << endl;
        }

        // Test sorted array
        arr = sortedArray;
        sortFunc(arr, 0, arr.size() - 1);
        if (is_sorted(arr.begin(), arr.end())) {
            cout << sortName << " successfully sorted a sorted array of size " << size << "." << endl;
        } else {
            cout << sortName << " failed to sort a sorted array of size " << size << "." << endl;
        }

        // Test reverse sorted array
        arr = reverseSortedArray;
        sortFunc(arr, 0, arr.size() - 1);
        if (is_sorted(arr.begin(), arr.end())) {
            cout << sortName << " successfully sorted a reverse sorted array of size " << size << "." << endl;
        } else {
            cout << sortName << " failed to sort a reverse sorted array of size " << size << "." << endl;
        }
    }
}

// Wrapper function for Heapsort to match the signature expected by testSort
void heapsortWrapper(std::vector<int>& arr, int low, int high) {
    (void) low;  // Unused parameter
    (void) high; // Unused parameter
    heapsort(arr);
}

int main() {
    testSort(quicksort, "Quicksort");
    testSort(heapsortWrapper, "Heapsort");
    testSort(mergesort, "Merge Sort");
    return 0;
}
