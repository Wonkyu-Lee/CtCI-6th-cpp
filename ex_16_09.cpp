//
// Created by blazeq on 2017. 11. 30..
//

#include "catch.hpp"

namespace ex_16_09 {

int mult(int a, int b) {
    // TODO: It works without considering minus.
    bool minus = ((a >> 31) ^ (b >> 31)) != 0;
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    int result = 0;
    int base = a;
    for (int i = 0; i < 32; ++i) {
        int mask = 1 << i;
        if (mask & b) {
            result += base;
        }
        base = base + base;
    }

    return minus ? -result : result;
}

int sub(int a, int b) {
    return a + (-b);
}

int div(int a, int b) {
    if (b == 0) {
        throw "Arithmetic error";
    }

    bool minus = ((a >> 31) ^ (b >> 31)) != 0;
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    int q = 0;
    while (a - b >= 0) {
        a -= b;
        ++q;
    }

    return minus ? -q : q;
}

TEST_CASE("16-09", "[16-09]") {
    REQUIRE(mult(245, -592) == -245 * 592);
    REQUIRE(mult(-14, 521) == -14 * 521);
    REQUIRE(mult(-481, -215) == 481 * 215);

    REQUIRE(sub(15, 3) == 15 - 3);
    REQUIRE(sub(245, -592) == 245 - (-592));

    REQUIRE(div(15, 3) == 15 / 3);
    REQUIRE(div(3, 4) == 3 / 4);
    REQUIRE(div(33, -4) == -33 / 4);
    REQUIRE(div(209523, 19) == 209523 / 19);
}

} // namespace ex_16_09