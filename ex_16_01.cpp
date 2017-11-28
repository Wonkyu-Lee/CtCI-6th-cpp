//
// Created by blazeq on 2017. 11. 28..
//

#include "catch.hpp"

namespace ex_16_01 {

void swap(int& a, int& b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

TEST_CASE("16-01", "[16-01]") {
    int a = 123;
    int b = 345;
    swap(a, b);
    REQUIRE((a == 345 && b == 123));
}

} // namespace ex_16_01