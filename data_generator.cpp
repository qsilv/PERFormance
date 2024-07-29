#include "data_generator.h"
#include <cstdlib>
#include <vector>

std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
    return arr;
}
