#include "algorithms/Algorithm.h"
#include <algorithm>

static void mergeSortRec(std::vector<int>& a, int lo, int hi,
                         std::vector<Step>& steps, const std::vector<bool>& sorted) {
    if (lo >= hi) return;
    const int mid = lo + (hi - lo) / 2;
    mergeSortRec(a, lo, mid, steps, sorted);
    mergeSortRec(a, mid + 1, hi, steps, sorted);

    std::vector<int> left(a.begin() + lo, a.begin() + mid + 1);
    std::vector<int> right(a.begin() + mid + 1, a.begin() + hi + 1);
    size_t i = 0, j = 0;
    int k = lo;

    while (i < left.size() && j < right.size()) {
        steps.push_back({a, k, mid + 1 + (int)j, -1, -1, sorted});
        a[k] = (left[i] <= right[j]) ? left[i++] : right[j++];
        steps.push_back({a, -1, -1, k, -1, sorted});   // red = value written
        ++k;
    }
    while (i < left.size())  { a[k] = left[i++];  steps.push_back({a, -1, -1, k, -1, sorted}); ++k; }
    while (j < right.size()) { a[k] = right[j++]; steps.push_back({a, -1, -1, k, -1, sorted}); ++k; }
}

std::vector<Step> mergeSort(std::vector<int> a) {
    std::vector<Step> steps;
    std::vector<bool> sorted(a.size(), false);
    mergeSortRec(a, 0, static_cast<int>(a.size()) - 1, steps, sorted);

    std::fill(sorted.begin(), sorted.end(), true);
    steps.push_back({a, -1, -1, -1, -1, sorted});
    return steps;
}