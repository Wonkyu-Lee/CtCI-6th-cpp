//
// Created by blazeq on 2017. 11. 9..
//

#include "catch.hpp"

namespace ex_10_03 {

int findIndexOfValue(int arr[], int p, int r, int value) {
    if (p > r)
        return -1;

    int q = (p + r) / 2;
    if (arr[q] == value) {
        return q;
    }

    if (arr[p] >= arr[r]) {
        int found = findIndexOfValue(arr, p, q - 1, value);
        if (found != -1) {
            return found;
        }
        return findIndexOfValue(arr, q + 1, r, value);
    } else {
        if (value < arr[p] || arr[r] < value)
            return -1;

        if (value < arr[q]) {
            return findIndexOfValue(arr, p, q - 1, value);
        } else {
            return findIndexOfValue(arr, q + 1, r, value);
        }
    }
}

int findIndexOfValue(int arr[], int n, int value) {
    return findIndexOfValue(arr, 0, n - 1, value);
}

TEST_CASE("10_03", "[10-03]") {
    {
        int arr[] = { 15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14 };
        int n = sizeof(arr) / sizeof(int);
        REQUIRE(findIndexOfValue(arr, n, 5) == 8);
        REQUIRE(findIndexOfValue(arr, n, 15) == 0);
        REQUIRE(findIndexOfValue(arr, n, 10) == 10);
    }

    {
        int arr[] = { 10, 15, 20, 0, 5 };
        int n = sizeof(arr) / sizeof(int);
        REQUIRE(findIndexOfValue(arr, n, 5) == 4);
    }

    {
        int arr[] = { 50, 5, 20, 30, 40 };
        int n = sizeof(arr) / sizeof(int);
        REQUIRE(findIndexOfValue(arr, n, 5) == 1);
    }

    {
        int arr[] = { 2, 2, 2, 3, 4, 2 };
        int n = sizeof(arr) / sizeof(int);
        REQUIRE(findIndexOfValue(arr, n, 4) == 4);
    }

}

} // namespace ex_10_03