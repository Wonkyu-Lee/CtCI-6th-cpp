//
// Created by blazeq on 2017. 11. 11..
//

#include "catch.hpp"

namespace ex_10_11 {

void peakAndValley(int arr[], int n) {
    for (int i = 0; i < n; i += 2) {
        int l = std::max(0, i - 1);
        int r = std::min(i + 1, n - 1);
        int maxIndex = l;
        int maxValue = arr[l];
        for (int j = l + 1; j <= r; ++j) {
            if (arr[j] > maxValue) {
                maxValue = arr[j];
                maxIndex = j;
            }
        }
        if (i != maxIndex) {
            std::swap(arr[i], arr[maxIndex]);
        }
    }
}

TEST_CASE("10-11", "[10-11]") {

    int arr[] = {5, 3, 1, 2, 3, 9, 8, 7, 4, 5, 6, 4};
    int n = sizeof(arr)/sizeof(int);
    peakAndValley(arr, n);
    for (int i = 0; i < n; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

} // namespace ex_10_11