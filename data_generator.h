#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <vector>

std::vector<int> generateRandomArray(int size);
std::vector<int> generateSortedArray(int size);
std::vector<int> generateReverseSortedArray(int size);
void printArray(const std::vector<int>& arr);

#endif // DATA_GENERATOR_H
