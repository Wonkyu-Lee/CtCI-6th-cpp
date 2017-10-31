//
// Created by blazeq on 2017. 10. 23..
//

#include <cstdint>
#include <cassert>
#include <iostream>
#include "catch.hpp"

namespace ex_06_08 {

using namespace std;

pair<int, int> findMinimumEggFallCount() {
    int h = 100;

    int interval = 0;
    int minimum = 100;

    for (int i = 2; i < 50; ++i) {
        int n = (h / i) + (i - 1) + (h - ((h / i) * i));
        if (n < minimum) {
            interval = i;
            minimum = n;
        }
    }

    return make_pair(interval, minimum);
}


TEST_CASE("06-08", "[06-08]") {
    auto v = findMinimumEggFallCount();
    printf("Minimum egg fall count: %d, interval: %d\n", v.second, v.first);
}

} // namespace ex_06_08