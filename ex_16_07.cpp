//
// Created by blazeq on 2017. 11. 30..
//

#include "catch.hpp"

namespace ex_16_07 {

int flip(int x) {
    return x ^ 0x1;
}

int sign(int x) {
    return flip((x >> 31) & 0x1);
}

int max(int a, int b) {
    int c = a - b;

    int sa = sign(a);
    int sb = sign(b);
    int sc = sign(c);

    int use_sign_of_a = sa ^ sb;
    int use_sign_of_c = flip(sa ^ sb);

    int k = use_sign_of_a * sa + use_sign_of_c * sc;
    int q = flip(k);

    return a * k + b * q;
}

TEST_CASE("16-07", "[16-07]") {
    REQUIRE(max(263, 924) == 924);
    REQUIRE(max(1263, 924) == 1263);
    REQUIRE(max(0, 77) == 77);
    REQUIRE(max(77, 0) == 77);
}

} // namespace ex_16_07