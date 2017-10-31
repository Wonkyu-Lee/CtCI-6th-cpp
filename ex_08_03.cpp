//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <iostream>
#include <list>

namespace ex_08_03 {

using namespace std;

namespace unique {

int findMagicIndex(int arr[], int p, int r) {
    if (p > r) {
        return -1;
    }

    int q = (p + r) / 2;

    if (arr[q] < q) {
        return findMagicIndex(arr, q + 1, r);
    } else if (q < arr[q]) {
        return findMagicIndex(arr, p, q - 1);
    } else {
        return q;
    }
}

void findMagicIndex(int arr[], int n, list<int>& result) {
    result.clear();

    int found = findMagicIndex(arr, 0, n - 1);
    if (found == -1)
        return;

    result.push_back(found);

    for (int i = found - 1; 0 <= i; --i) {
        if (arr[i] != i)
            break;

        result.push_front(i);
    }

    for (int i = found + 1; i < n; ++i) {
        if (arr[i] != i)
            break;
        result.push_back(i);
    }
}

} // namespace unique

namespace redundant {

void findMagicIndex(int arr[], int n, list<int>& result) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == i) {
            result.push_back(i);
        }
    }
}

} // namespace redundant

TEST_CASE("08-03", "[08-03]") {

    SECTION("Unique sequence") {
        //            0   1  2  3  4  5  6  7  8   9  10
        int arr[] = {-5, -3, 0, 1, 2, 5, 6, 7, 8, 11, 14};

        list<int> result;
        unique::findMagicIndex(arr, 11, result);

        list<int> expected;
        expected.push_back(5);
        expected.push_back(6);
        expected.push_back(7);
        expected.push_back(8);

        REQUIRE(result.size() == expected.size());
        auto i = result.begin();
        auto j = expected.begin();
        for (;
                i != result.end();
                ++i, ++j) {
            REQUIRE(*i == *j);
        }
    }

    SECTION("Redundant sequence") {
        //            0   1  2  3  4  5  6  7  8  9 10
        int arr[] = { 0,  1, 2, 2, 3, 3, 6, 7, 9, 9, 9};

        list<int> result;
        redundant::findMagicIndex(arr, 11, result);

        list<int> expected;
        expected.push_back(0);
        expected.push_back(1);
        expected.push_back(2);
        expected.push_back(6);
        expected.push_back(7);
        expected.push_back(9);

        REQUIRE(result.size() == expected.size());
        auto i = result.begin();
        auto j = expected.begin();
        for (;
                i != result.end();
                ++i, ++j) {
            REQUIRE(*i == *j);
        }
    }
}

} // namespace ex_08_03