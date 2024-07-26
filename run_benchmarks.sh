#!/bin/bash

# Compile with different optimization levels
g++ -O0 benchmark.cpp data_generator.cpp quicksort.cpp heapsort.cpp mergesort.cpp -o benchmark_O0
g++ -O2 benchmark.cpp data_generator.cpp quicksort.cpp heapsort.cpp mergesort.cpp -o benchmark_O2
g++ -O3 benchmark.cpp data_generator.cpp quicksort.cpp heapsort.cpp mergesort.cpp -o benchmark_O3

# Function to run benchmarks with perf
run_perf() {
    echo "Running with $1 optimization:"
    sudo perf stat -e branch-misses,cache-misses -x, -o perf_output_$1.txt ./benchmark_$1
    echo "Perf output saved to perf_output_$1.txt"
}

# Run benchmarks
run_perf O0
run_perf O2
run_perf O3
