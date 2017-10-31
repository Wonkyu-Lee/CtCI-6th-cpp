//
// Created by blazeq on 2017. 10. 17..
//

#include <cstdint>
#include <cassert>
#include <iostream>
#include "catch.hpp"

namespace ex_06_01 {

using namespace std;

namespace solutionByQ {

int findBottle(int heavyBottle) {
    // do not use float for equality comparison.
    // I multiplied 10 to weight of each pill; 1.1 => 11, 1.0 => 10
    auto weights = vector<int>(20, 0);
    auto counts = vector<int> {
        1,  2,   3,  4,  5,  6,  7,  8,  9, 11,
        12, 13, 14, 15, 16, 17, 18, 19, 21, 22
    };

    for (int i = 0; i < 20; ++i) {
        weights[i] = 11 * counts[i];
        for (int j = 0; j < 20; ++j) {
            if (j != i) {
                weights[i] += 10 * counts[j];
            }
        }
    }

    // print bottle weights
//    for (int i = 0; i < 20; ++i) {
//        printf("Bottle#%2d: %3.1f gram\n", i + 1, weights[i]/10.0f);
//    }

    int weight = weights[heavyBottle - 1];
    for (int i = 0; i < 20; ++i) {
        if (weights[i] == weight) {
            return i + 1;
        }
    }

    return 0;
}

} // solutionByQ


TEST_CASE("06-01", "[06-01]") {
    SECTION("Solution by Q") {
        using namespace solutionByQ;

        for (int heavyBottle = 1; heavyBottle <= 20; ++heavyBottle) {
            REQUIRE(findBottle(heavyBottle) == heavyBottle);
        }
    }
}

} // namespace ex_06_01