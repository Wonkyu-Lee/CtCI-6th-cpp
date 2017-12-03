//
// Created by blazeq on 2017. 12. 3..
//

#include <algorithm>
#include <vector>
#include "catch.hpp"

namespace ex_16_17 {

using namespace std;

tuple<int, int> findSequenceOfLargestSum(const vector<int>& array) {
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

    return make_tuple(start, length);
};

TEST_CASE("16-17", "[16-17]") {
    int start, length;
    tie(start, length) = findSequenceOfLargestSum({-8, 3, -2, 4, -10});
    REQUIRE(start == 1);
    REQUIRE(length == 3);
}

} // namespace ex_16_17