//
// Created by blazeq on 2017. 11. 30..
//

#include "catch.hpp"

namespace ex_16_07 {

int max(int a, int b) {
    int sign = (a - b) & (1 << 31);
    int mask = (sign >> 31);
    return (b & mask) + (a & ~mask);
}

TEST_CASE("16-07", "[16-07]") {
    REQUIRE(max(263, 924) == 924);
    REQUIRE(max(1263, 924) == 1263);
    REQUIRE(max(0, 77) == 77);
    REQUIRE(max(77, 0) == 77);
}

} // namespace ex_16_07