#pragma once
#include <string>
#include <vector>
#include "Step.h"

using AlgorithmFn = std::vector<Step> (*)(std::vector<int>);

struct AlgorithmInfo {
    std::string name;
    std::string bigO;
    AlgorithmFn fn;
};

std::vector<Step> bubbleSort(std::vector<int> a);
std::vector<Step> insertionSort(std::vector<int> a);
std::vector<Step> mergeSort(std::vector<int> a);
std::vector<Step> quickSort(std::vector<int> a);

const std::vector<AlgorithmInfo>& getAlgorithms();