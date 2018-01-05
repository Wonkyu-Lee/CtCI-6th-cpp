//
// Created by blazeq on 2018. 1. 3..
//

#include "catch.hpp"

namespace ex_17_10 {

int findCandidate(int array[], int n) {
    if (n <= 0) return -1;

    int count = 0;
    int majority = -1;
    for (int i = 0; i < n; ++i) {
        if (count == 0) {
            majority = array[i];
        }

        if (array[i] == majority) {
            ++count;
        } else {
            --count;
        }
    }

    return majority;
}

bool isMajority(int array[], int n, int candidate) {
    if (n <= 0) return false;
    if (candidate == -1) return false;

    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (array[i] == candidate) {
            ++count;
        }
    }

    return count > n / 2;
}

int findMajority(int array[], int n) {
    int candidate = findCandidate(array, n);
    return  isMajority(array, n, candidate) ? candidate : -1;
}

TEST_CASE("17-10", "[17-10]") {
    int array[] = {1, 2, 5, 9, 5, 9, 5, 5, 5};
    REQUIRE(findMajority(array, 9) == 5);
}

} // namespace ex_17_10