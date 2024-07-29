#!/bin/bash

COMPILER_FLAGS=("O0" "O1" "O2" "O3")
ARRAY_SIZES=(10000 50000 100000 500000 1000000)
SORTING_ALGORITHMS=("MergeSort" "HeapSort" "QuickSort")
RESULTS_FILE="benchmark_results.txt"
P_CORES="0-15"  # Adjust based on your system's P-cores

# Clear the results file
echo "Benchmarking Results" > $RESULTS_FILE
echo "====================" >> $RESULTS_FILE

for FLAG in "${COMPILER_FLAGS[@]}"
do
    g++ -std=c++11 -$FLAG sorting_benchmark.cpp -o sorting_benchmark_$FLAG
    echo "Benchmarking with -$FLAG optimization" | tee -a $RESULTS_FILE
    
    for SIZE in "${ARRAY_SIZES[@]}"
    do
        for SORT in "${SORTING_ALGORITHMS[@]}"
        do
            echo "Array Size: $SIZE, Algorithm: $SORT" | tee -a $RESULTS_FILE
            echo "Running on P-cores: $P_CORES" | tee -a $RESULTS_FILE
            taskset -c $P_CORES ./sorting_benchmark_$FLAG $SIZE $SORT > temp_output.txt
            cat temp_output.txt >> $RESULTS_FILE
            taskset -c $P_CORES perf stat -e cache-misses,branch-misses ./sorting_benchmark_$FLAG $SIZE $SORT 2>> $RESULTS_FILE
            echo "" >> $RESULTS_FILE
        done
    done
done

echo "Benchmarking completed. Results are saved in $RESULTS_FILE."
