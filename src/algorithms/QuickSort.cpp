#include "algorithms/Algorithm.h"
#include <algorithm>

static int partition(std::vector<int>& a, int lo, int hi,
                     std::vector<Step>& steps, const std::vector<bool>& sorted) {
    const int pivot = a[hi];
    int i = lo;
    for (int j = lo; j < hi; ++j) {
        steps.push_back({a, j, hi, -1, -1, sorted});    // hi = pivot, stays yellow
        if (a[j] < pivot) {
            if (i != j) {
                std::swap(a[i], a[j]);
                steps.push_back({a, -1, -1, i, j, sorted});
            }
            ++i;
        }
    }
    std::swap(a[i], a[hi]);
    steps.push_back({a, -1, -1, i, hi, sorted});
    return i;
}

static void quickSortRec(std::vector<int>& a, int lo, int hi,
                         std::vector<Step>& steps, std::vector<bool>& sorted) {
    if (lo > hi) return;
    if (lo == hi) { sorted[lo] = true; return; }
    const int p = partition(a, lo, hi, steps, sorted);
    sorted[p] = true;                                   // pivot is in its final spot
    quickSortRec(a, lo, p - 1, steps, sorted);
    quickSortRec(a, p + 1, hi, steps, sorted);
}

std::vector<Step> quickSort(std::vector<int> a) {
    std::vector<Step> steps;
    std::vector<bool> sorted(a.size(), false);
    quickSortRec(a, 0, static_cast<int>(a.size()) - 1, steps, sorted);

    std::fill(sorted.begin(), sorted.end(), true);
    steps.push_back({a, -1, -1, -1, -1, sorted});
    return steps;
}