#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Function to generate a random array
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100000);

    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }

    return arr;
}

// Function to generate a sorted array
std::vector<int> generateSortedArray(int size) {
    std::vector<int> arr = generateRandomArray(size);
    std::sort(arr.begin(), arr.end());
    return arr;
}

// Function to generate a reverse-sorted array
std::vector<int> generateReverseSortedArray(int size) {
    std::vector<int> arr = generateRandomArray(size);
    std::sort(arr.begin(), arr.end(), std::greater<int>());
    return arr;
}

// Function to print an array (for demonstration purposes)
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

