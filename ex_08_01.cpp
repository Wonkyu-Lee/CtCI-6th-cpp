//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <iostream>

namespace ex_08_01 {

using namespace std;

namespace solution1 {

int countUpwardWays(int n) {
    if (n < 0)
        return 0;

    if (n == 0)
        return 1;

    return countUpwardWays(n - 1) + countUpwardWays(n - 2) + countUpwardWays(n - 3);
}

} // namespace solution1

namespace solution2 {

int countUpwardWays(int n, int m[]) {
    if (n < 0)
        return 0;

    if (m[n] != -1)
        return m[n];

    if (n == 0) {
        m[n] = 1;
    } else {
        m[n] = countUpwardWays(n - 1, m) + countUpwardWays(n - 2, m) + countUpwardWays(n - 3, m);
    }

    return m[n];
}

int countUpwardWays(int n) {
    int m[n + 1];
    std::fill(m, m + n + 1, -1);
    return countUpwardWays(n, m);
}

} // namespace solution2

namespace solution3 {

int countUpwardWays(int n) {
    if (n < 0)  return 0;
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 2;

    int a = 1;
    int b = 1;
    int c = 2;
    for (int i = 3; i < n; ++i) {
        int d = a + b + c;
        a = b;
        b = c;
        c = d;
    }

    return a + b + c;
}

} // namespace solution3

TEST_CASE("08-01", "[08-01]") {
    REQUIRE(solution1::countUpwardWays(10) == 274);
    REQUIRE(solution2::countUpwardWays(10) == 274);
    REQUIRE(solution3::countUpwardWays(10) == 274);

    // overflow!!!
    printf("countUpwardWays(%d) = %d\n", 36, solution3::countUpwardWays(37));
}

} // namespace ex_08_01