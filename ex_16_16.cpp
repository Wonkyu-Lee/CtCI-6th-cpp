//
// Created by blazeq on 2017. 12. 3..
//

#include <algorithm>
#include <vector>
#include <cassert>
#include "catch.hpp"

namespace ex_16_16 {

using namespace std;

int findPosition(const vector<int>& arr, int last, int value) {
    int p = 0;
    int r = last;

    while (p <= r) {
        int q = (p + r) / 2;

        if (value < arr[q]) {
            r = q - 1;
        } else if (arr[q] < value) {
            p = q + 1;
        } else {
            while (arr[q] == value) {
                ++q;
            }
            return q;
        }
    }

    assert (p > r);
    return p;
}

tuple<int, int> getMinSortRange(const vector<int>& arr) {
    int front = arr.size() - 1;
    int last = -1;
    int maxValue = numeric_limits<int>::min();

    for (int i = 0; i < arr.size(); ++i) {
        if (maxValue < arr[i]) {
            maxValue = arr[i];
        } else if (maxValue == arr[i]) {
            // do nothing
        } else {
            last = i;
            int p = findPosition(arr, i - 1, arr[i]);
            if (p < front) {
                front = p;
            }
        }
    }

    return make_tuple(front, last);
};

TEST_CASE("16-16", "[16-16]") {
    {
        int front, last;
        tie(front, last) = getMinSortRange({1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19});
        REQUIRE(front == 3);
        REQUIRE(last == 9);
    }

    {
        int front, last;
        tie(front, last) = getMinSortRange({1, 2, 4, 7, 10, 11});
        REQUIRE(last < 0);
    }

    {
        int front, last;
        tie(front, last) = getMinSortRange({11, 10, 7, 4, 2, 1});
        REQUIRE(front == 0);
        REQUIRE(last == 5);
    }

    {
        int front, last;
        tie(front, last) = getMinSortRange({1, 2, 4, 7, 7, 7, 7, 10, 11, 7, 12, 7, 10, 16, 18, 19});
        REQUIRE(front == 7);
        REQUIRE(last == 12);
    }
}

} // namespace ex_16_16