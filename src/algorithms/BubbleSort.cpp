#include "algorithms/Algorithm.h"
#include <algorithm>

std::vector<Step> bubbleSort(std::vector<int> a) {
    std::vector<Step> steps;
    std::vector<bool> sorted(a.size(), false);
    int n = static_cast<int>(a.size());

    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            steps.push_back({a, j, j + 1, -1, -1, sorted});
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                swapped = true;
                steps.push_back({a, -1, -1, j, j + 1, sorted});
            }
        }
        sorted[n - 1 - i] = true;
        if (!swapped) break;
    }

    std::fill(sorted.begin(), sorted.end(), true);
    steps.push_back({a, -1, -1, -1, -1, sorted});
    return steps;
}