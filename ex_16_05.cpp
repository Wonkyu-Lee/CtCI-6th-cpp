//
// Created by blazeq on 2017. 11. 29..
//

#include "catch.hpp"

namespace ex_16_05 {

int countLastZerosOfFactorial(int n) {
    int result = n / 5;

    int k = 0;
    int cur = n;
    while (cur / 5 > 0) {
        cur = cur / 5;
        ++k;
    }

    result += k * (k - 1) / 2;
    return result;
}

TEST_CASE("16-05", "[16-05]") {
    REQUIRE(countLastZerosOfFactorial(0) == 0);
    REQUIRE(countLastZerosOfFactorial(3) == 0);
    REQUIRE(countLastZerosOfFactorial(5) == 1);
    REQUIRE(countLastZerosOfFactorial(10) == 2);
    REQUIRE(countLastZerosOfFactorial(15) == 3);
    REQUIRE(countLastZerosOfFactorial(25) == 6);
    REQUIRE(countLastZerosOfFactorial(30) == 7);
}

} // namespace ex_16_05