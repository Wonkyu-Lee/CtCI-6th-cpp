//
// Created by blazeq on 2037. 10. 17..
//

#include <cstdint>
#include <cassert>
#include <iostream>
#include "catch.hpp"

namespace ex_05_03 {

using namespace std;

namespace solutionByQ {

// get the longest size of continuous 1s after toggle one zero bit
int getSizeOf1s(unsigned int x) {
    if (x == (~0))
        return sizeof(x) * 8;

    int maxCount = 0;
    int i = 0;
    int j = -1;
    int lCount = 0;
    int rCount = 0;
    for (; i < 32; ++i) {
        if (((1 << i) & x) == 0) {
            lCount = i - j - 1;
            int newCount = lCount + 1 + rCount;
            if (maxCount < newCount) {
                maxCount = newCount;
            }
            rCount = lCount;
            j = i;
        }
    }

    return maxCount;
}

} // solutionByQ


TEST_CASE("05-03", "[05-03]") {
    SECTION("Solution by Q") {
        using namespace solutionByQ;

        /*
         * 00111000
         *        ij -> newCount == 0 + 1 + 0 = 1
         * 00111000
         *        ij -> newCount == 0 + 1 + 0 = 1
         * 00111000
         *       ij  -> newCount == 0 + 1 + 0 = 1
         * 00111000
         *      ij   -> newCount == 0 + 1 + 0 = 1
         * 00111000
         *  i   j    -> newCount == 3 + 1 + 0 = 4
         * 00111000
         * ij        -> newCount == 0 + 1 + 3 = 4
         */
        REQUIRE(getSizeOf1s(0b00111000 == 4));

        REQUIRE(getSizeOf1s(~0) == sizeof(unsigned int) * 8);
        REQUIRE(getSizeOf1s(0) == 1);
        REQUIRE(getSizeOf1s(0b111) == 4);
        REQUIRE(getSizeOf1s(0b11011101111) == 8);
        REQUIRE(getSizeOf1s(0b110111111011101111) == 10);
    }
}

} // namespace ex_05_03