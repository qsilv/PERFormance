#!/bin/bash

COMPILER_FLAGS=("O0" "O1" "O2" "O3")
ARRAY_SIZES=(10000 50000 100000 500000 1000000)
SORTING_ALGORITHMS=("MergeSort" "HeapSort" "QuickSort")

for FLAG in "${COMPILER_FLAGS[@]}"
do
    g++ -std=c++11 -$FLAG sorting_benchmark.cpp -o sorting_benchmark_$FLAG
    echo "Benchmarking with -$FLAG optimization"
    
    for SIZE in "${ARRAY_SIZES[@]}"
    do
        for SORT in "${SORTING_ALGORITHMS[@]}"
        do
            echo "Array Size: $SIZE, Algorithm: $SORT"
            perf stat -e cache-misses,branch-misses ./sorting_benchmark_$FLAG $SIZE $SORT
        done
    done
done
