#include "algorithms/Algorithm.h"

const std::vector<AlgorithmInfo>& getAlgorithms() {
        static const std::vector<AlgorithmInfo> algos = {
        {"Bubble Sort",    "O(n^2)",                     bubbleSort},
        {"Insertion Sort", "O(n^2)",                     insertionSort},
        {"Merge Sort",     "O(n log n)",                 mergeSort},
        {"Quick Sort",     "O(n log n) avg, O(n^2) worst", quickSort},
    };
    return algos;
}