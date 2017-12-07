//
// Created by blazeq on 2017. 12. 3..
//

#include <algorithm>
#include <vector>
#include "catch.hpp"

namespace ex_16_17 {

using namespace std;

tuple<int, int, int> findSequenceOfLargestSum(const vector<int>& array) {
    int maxSum = numeric_limits<int>::min();
    int start = -1;
    int length = 0;
    for (size_t count = 1; count <= array.size(); ++count) {
        for (size_t i = 0; count <= array.size() - i; ++i) {
            int sum = 0;
            for (size_t j = 0; j < count; ++j) {
                sum += array[i + j];
            }
            if (sum > maxSum) {
                maxSum = sum;
                start = i;
                length = count;
            }
        }
    }

    return make_tuple(maxSum, start, length);
};

tuple<int, int, int> findSequenceOfLargestSum2(const vector<int>& array) {
    int maxSum = numeric_limits<int>::min();
    int start = -1;
    int length = 0;
    vector<int> prev(array.size(), 0);
    for (size_t count = 1; count <= array.size(); ++count) {
        for (size_t i = 0; count <= array.size() - i; ++i) {
            int sum = prev[i] + array[i + count - 1];
            if (sum > maxSum) {
                maxSum = sum;
                start = i;
                length = count;
            }
            prev[i] = sum;
        }
    }

    return make_tuple(maxSum, start, length);
};

tuple<int, int, int> findSequenceOfLargestSum3(const vector<int>& array) {
    int maxSum = 0;
    int start = 0;
    int end = 0;
    int sum = 0;
    int newStart = 0;
    for (size_t i = 0; i < array.size(); ++i) {
        sum += array[i];
        if (sum > maxSum) {
            maxSum = sum;
            start = newStart;
            end = i;
        } else if (sum < 0) {
            sum = 0;
            newStart = i + 1;
        }
    }

    return make_tuple(maxSum, start, end - start + 1);
};

TEST_CASE("16-17", "[16-17]") {
    {
        int maxSum, start, length;
        tie(maxSum, start, length) = findSequenceOfLargestSum3({-8, 3, -2, 4, -10});
        REQUIRE(maxSum == 5);
        REQUIRE(start == 1);
        REQUIRE(length == 3);
    }

    // TODO:!!!
    {
        int maxSum, start, length;
        tie(maxSum, start, length) = findSequenceOfLargestSum3({-8, -3, -2, -4, -10});
        REQUIRE(maxSum == -2);
        REQUIRE(start == 2);
        REQUIRE(length == 1);
    }
}

} // namespace ex_16_17