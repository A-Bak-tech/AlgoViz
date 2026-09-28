#pragma once
#include <vector>

struct Step {
    std::vector<int> array;
    int cmpA = -1, cmpB = -1;
    int swapA = -1, swapB = -1;
    std::vector<bool> sorted;
    int comparisons = 0;   // running totals, filled in by Player
    int swaps = 0;
};