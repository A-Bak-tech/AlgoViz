#include "algorithms/Algorithm.h"
#include <algorithm>

std::vector<Step> insertionSort(std::vector<int> a) {
    std::vector<Step> steps;
    const int n = static_cast<int>(a.size());
    std::vector<bool> sorted(n, false);
    if (n > 0) sorted[0] = true;

    for (int i = 1; i < n; ++i) {
        int j = i;
        while (j > 0) {
            steps.push_back({a, j - 1, j, -1, -1, sorted});
            if (a[j - 1] <= a[j]) break;
            std::swap(a[j - 1], a[j]);
            steps.push_back({a, -1, -1, j - 1, j, sorted});
            --j;
        }
        sorted[i] = true;   // green = sorted-so-far prefix
    }

    std::fill(sorted.begin(), sorted.end(), true);
    steps.push_back({a, -1, -1, -1, -1, sorted});
    return steps;
}