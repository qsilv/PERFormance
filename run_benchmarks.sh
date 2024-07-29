#!/bin/bash

# Compile with different optimization levels
compile() {
    optimization_level=$1
    echo "Compiling with optimization level -$optimization_level"
    g++ -$optimization_level benchmark.cpp data_generator.cpp quicksort.cpp heapsort.cpp mergesort.cpp -o benchmark_$optimization_level
}

# Run benchmarks and use perf to gather performance statistics
run_benchmarks() {
    optimization_level=$1
    sort_name=$2
    echo "Running benchmarks with $sort_name and optimization level -$optimization_level"
    perf stat -e branch-misses,cache-misses -x, -o perf_output_${sort_name}_$optimization_level.txt ./benchmark_$optimization_level $sort_name $optimization_level
    echo "Perf output saved to perf_output_${sort_name}_$optimization_level.txt"
}

# Main execution
main() {
    sort_names=("Quicksort" "Heapsort" "Merge Sort")
    optimization_levels=("O0" "O2" "O3")

    # Compile with each optimization level
    for opt_level in "${optimization_levels[@]}"; do
        compile $opt_level
    done

    # Run benchmarks for each sort algorithm and optimization level
    for sort_name in "${sort_names[@]}"; do
        for opt_level in "${optimization_levels[@]}"; do
            run_benchmarks $opt_level $sort_name
        done
    done
}

# Execute the main function
main
