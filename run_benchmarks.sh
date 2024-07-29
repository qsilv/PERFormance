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
    output_file=$3

    echo "Running benchmarks with $sort_name and optimization level -$optimization_level"
    ./benchmark_$optimization_level $sort_name $optimization_level $output_file

    # Use perf to gather statistics and append to the output file
    sudo perf stat -e branch-misses,cache-misses -x, -o temp_perf_output.txt ./benchmark_$optimization_level $sort_name $optimization_level $output_file
    echo "Perf output for $sort_name with $optimization_level optimization:" >> $output_file
    cat temp_perf_output.txt >> $output_file
    echo "" >> $output_file

    rm temp_perf_output.txt
}

# Main execution
main() {
    sort_names=("Quicksort" "Heapsort" "Merge Sort")
    optimization_levels=("O0" "O2" "O3")
    output_file="benchmark_results.txt"

    # Clear the output file
    echo "Sort Algorithm, Array Size, Optimization Level, Runtime" > $output_file

    # Compile with each optimization level
    for opt_level in "${optimization_levels[@]}"; do
        compile $opt_level
    done

    # Run benchmarks for each sort algorithm and optimization level
    for sort_name in "${sort_names[@]}"; do
        for opt_level in "${optimization_levels[@]}"; do
            run_benchmarks $opt_level $sort_name $output_file
        done
    done
}

# Execute the main function
main
