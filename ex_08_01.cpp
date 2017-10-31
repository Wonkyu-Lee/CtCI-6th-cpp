//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <iostream>

namespace ex_08_01 {

using namespace std;

namespace sol1 {

int countUpwardWays(int n) {
    if (n == 1) return 1; // (1)
    if (n == 2) return 2; // (1, 1), (2)
    if (n == 3) return 4; // (1, 1, 1), (2, 1), (1, 2), (3)
    return countUpwardWays(n - 1) + countUpwardWays(n - 2) + countUpwardWays(n - 3);
}

} // namespace sol1

namespace sol2 {

int countUpwardWays(int n) {
    if (n == 1) return 1; // (1)
    if (n == 2) return 2; // (1, 1), (2)
    if (n == 3) return 4; // (1, 1, 1), (2, 1), (1, 2), (3)

    int a = 1;
    int b = 2;
    int c = 4;

    for (int i = 4; i < n; ++i) {
        int d = a + b + c;
        a = b;
        b = c;
        c = d;
    }

    return a + b + c;
}

} // namespace sol2

TEST_CASE("08-01", "[08-01]") {
    REQUIRE(sol1::countUpwardWays(10) == 274);
    REQUIRE(sol2::countUpwardWays(10) == 274);
}

} // namespace ex_08_01