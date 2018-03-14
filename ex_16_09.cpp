//
// Created by blazeq on 2017. 11. 30..
//

#include "catch.hpp"
#include <stack>
using namespace std;

namespace ex_16_09 {

namespace solution1 {
int mul(int a, int b) {
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
} // namespace solution1


namespace solution2 {

int sign(int x) {
    return x >= 0 ? 0 : 1;
}

int neg(int x) {
    int prevSign = sign(x);
    int y = 0;
    int d = x < 0 ? 1 : -1;

    stack<int> st;
    while (x != 0) {
        // d를 검토
        while (true) {
            int newSign = sign(x + d);
            if (x + d == 0 || prevSign == newSign) {
                break;
            }

            d = st.top(); st.pop();
        }

        st.push(d);
        x += d;
        y += d;

        // d를 두 배로 증가
        d += d;
    }

    return y;
}

int abs(int x) {
    return x < 0 ? neg(x) : x;
}

int sub(int a, int b) {
    return a + neg(b);
}

int mul(int a, int b) {
    if (abs(a) < abs(b)) {
        return mul(b, a);
    }

    int sum = 0;
    for (int i = 0; i < abs(b); ++i) {
        sum += a;
    }

    if (b < 0) {
        sum = neg(sum);
    }

    return sum;
}

int div(int a, int b) {
    if (b == 0) {
        throw "Divide by 0";
    }

    int a2 = abs(a);
    int b2 = abs(b);

    int q = 0;
    while (sub(a2, b2) >= 0) {
        a2 = sub(a2, b2);
        ++q;
    }

    if (sign(a) != sign(b)) {
        q = neg(q);
    }

    return q;
}

} // namespace solution2


TEST_CASE("16-09", "[16-09]") {

    SECTION("Solution 1") {
        using namespace solution1;
        REQUIRE(mul(245, -592) == -245 * 592);
        REQUIRE(mul(-14, 521) == -14 * 521);
        REQUIRE(mul(-481, -215) == 481 * 215);

        REQUIRE(sub(15, 3) == 15 - 3);
        REQUIRE(sub(245, -592) == 245 - (-592));

        REQUIRE(div(15, 3) == 15 / 3);
        REQUIRE(div(3, 4) == 3 / 4);
        REQUIRE(div(33, -4) == -33 / 4);
        REQUIRE(div(209523, 19) == 209523 / 19);
    }

    SECTION("Solution 2") {
        using namespace solution2;
        REQUIRE(neg(156) == -156);
        REQUIRE(neg(-1035) == 1035);

        REQUIRE(mul(245, -592) == -245 * 592);
        REQUIRE(mul(-14, 521) == -14 * 521);
        REQUIRE(mul(-481, -215) == 481 * 215);

        REQUIRE(sub(15, 3) == 15 - 3);
        REQUIRE(sub(245, -592) == 245 - (-592));

        REQUIRE(div(15, 3) == 15 / 3);
        REQUIRE(div(3, 4) == 3 / 4);
        REQUIRE(div(33, -4) == -33 / 4);
        REQUIRE(div(209523, 19) == 209523 / 19);
    }
}

} // namespace ex_16_09