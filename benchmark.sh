#!/bin/bash

# Prompt user for input
read -p "Enter array sizes (space-separated): " -a ARRAY_SIZES
read -p "Enter compiler flags (space-separated, e.g., O0 O1 O2 O3): " -a COMPILER_FLAGS
read -p "Enter sorting algorithms (space-separated, e.g., MergeSort HeapSort QuickSort BubbleSort InsertionSort SelectionSort): " -a SORTING_ALGORITHMS

RESULTS_FILE="benchmark_results.txt"

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
            
            # Run the benchmark and capture runtime
            ./sorting_benchmark_$FLAG $SIZE $SORT > temp_output.txt
            cat temp_output.txt >> $RESULTS_FILE

            # Collect performance statistics
            perf stat -e L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./sorting_benchmark_$FLAG $SIZE $SORT 2> perf_output.txt
            # Clean up perf output
            grep -E 'L1-dcache-load-misses|L1-dcache-loads|LLC-load-misses|LLC-loads' perf_output.txt | tee -a $RESULTS_FILE

            # Record detailed performance data for analysis
            perf record -e L1-dcache-load-misses:pp,L1-dcache-loads:pp,LLC-load-misses:pp,LLC-loads:pp ./sorting_benchmark_$FLAG $SIZE $SORT
            
            echo "" >> $RESULTS_FILE
        done
    done
done

echo "Benchmarking completed. Results are saved in $RESULTS_FILE."
