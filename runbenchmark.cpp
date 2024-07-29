#include <iostream>
#include <cstdlib>
#include "benchmark.cpp"

using namespace std;

void runPerf(const string& sortName, const string& optimizationLevel) {
    string command = "sudo perf stat -e branch-misses,cache-misses -x, -o perf_output_" + sortName + "_" + optimizationLevel + ".txt ./benchmark_" + sortName + "_" + optimizationLevel;
    
    cout << "Running with " << sortName << " and " << optimizationLevel << " optimization:" << endl;
    system(command.c_str());
    
    cout << "Perf output saved to perf_output_" << sortName << "_" + optimizationLevel + ".txt" << endl;
}

int main() {
    vector<string> sortNames = {"Quicksort", "Heapsort", "Merge Sort"};
    vector<string> optimizationLevels = {"O0", "O2", "O3"};

    for (const string& sortName : sortNames) {
        for (const string& optimizationLevel : optimizationLevels) {
            cout << "Starting benchmarks with " << sortName << " and " << optimizationLevel << " optimization" << endl;
            string compileCommand = "g++ -" + optimizationLevel + " -o benchmark_" + sortName + "_" + optimizationLevel + " benchmark.cpp data_generator.cpp quicksort.cpp heapsort.cpp mergesort.cpp";
            system(compileCommand.c_str());
            runPerf(sortName, optimizationLevel);
            cout << "Finished benchmarks with " << sortName << " and " << optimizationLevel << " optimization" << endl;
        }
    }

    return 0;
}
