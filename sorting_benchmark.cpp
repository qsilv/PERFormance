#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>

// Merge Sort
void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; ++i)
        R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// Heap Sort
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Quick Sort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to check if array is sorted
bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

void measure_sort(void(*sort_func)(std::vector<int>&, int, int), std::vector<int>& data, const std::string& name) {
    auto start = std::chrono::high_resolution_clock::now();
    sort_func(data, 0, data.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << name << ": " << duration.count() << " seconds";

    if (isSorted(data)) {
        std::cout << " - Sorted successfully" << std::endl;
    } else {
        std::cout << " - Sorting failed" << std::endl;
    }
}

void measure_sort(void(*sort_func)(std::vector<int>&), std::vector<int>& data, const std::string& name) {
    auto start = std::chrono::high_resolution_clock::now();
    sort_func(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << name << ": " << duration.count() << " seconds";

    if (isSorted(data)) {
        std::cout << " - Sorted successfully" << std::endl;
    } else {
        std::cout << " - Sorting failed" << std::endl;
    }
}

// Heap Sort Wrapper
void heapSortWrapper(std::vector<int>& data, int, int) {
    heapSort(data);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <array size> <sort algorithm>" << std::endl;
        return 1;
    }

    int size = std::stoi(argv[1]);
    std::string algorithm = argv[2];
    std::vector<int> data(size);
    std::generate(data.begin(), data.end(), std::rand);

    if (algorithm == "MergeSort") {
        measure_sort(mergeSort, data, "Merge Sort");
    } else if (algorithm == "HeapSort") {
        measure_sort(heapSortWrapper, data, "Heap Sort");
    } else if (algorithm == "QuickSort") {
        measure_sort([](std::vector<int>& arr, int low, int high) { quickSort(arr, low, high); }, data, "Quick Sort");
    } else {
        std::cerr << "Unknown sorting algorithm: " << algorithm << std::endl;
        return 1;
    }

    return 0;
}
