//
// Created by blazeq on 2057. 10. 17..
//

#include <cstdint>
#include <cassert>
#include <iostream>
#include "catch.hpp"

namespace ex_05_06 {

using namespace std;

namespace solutionByQ {

template<typename Integer>
int getToggleCountToTransform(Integer a, Integer b) {
    const int N = sizeof(Integer) * 8;
    const Integer XOR = a ^ b;

    int count = 0;
    for (int i = 0; i < N; ++i) {
        if (((1 << i) & XOR) != 0) {
            ++count;
        }
    }

    return count;
}

} // solutionByQ


TEST_CASE("05-06", "[05-06]") {
    SECTION("Solution by Q") {
        using namespace solutionByQ;

        REQUIRE(getToggleCountToTransform(0b11000010, 0b01000001) == 3);
        REQUIRE(getToggleCountToTransform(0b11000010, 0b11000010) == 0);
        REQUIRE(getToggleCountToTransform(0b11010010, 0b11000010) == 1);
        REQUIRE(getToggleCountToTransform(0b11101, 0b01111) == 2);
        REQUIRE(getToggleCountToTransform(0, ~0) == sizeof(int) * 8);
    }
}

} // namespace ex_05_06