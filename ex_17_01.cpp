//
// Created by blazeq on 2017. 12. 8..
//

#include "catch.hpp"
#include <iostream>

namespace ex_17_01 {

namespace mine {

int add(int a, int b) {
    int sum = 0;
    bool carry = false;
    for (int i = 0; i < 32; ++i) {
        int mask = 1 << i;
        int aBit = a & mask;
        int bBit = b & mask;
        if (carry) {
            int carryBit = 1 << i;
            sum = sum | (aBit ^ bBit ^ carryBit);
            carry = (aBit | bBit) != 0;
        } else {
            sum = sum | (aBit ^ bBit);
            carry = (aBit & bBit) != 0;
        }
    }
    return sum;
}

} // namespace mine

namespace solution1 {

int add(int a, int b) {
    if (b == 0)
        return a;

    int sum = a ^ b;
    int carry = (a & b) << 1;
    return add(sum, carry);
}

} // namespace solution1

namespace solution2 {

int add(int a, int b) {
    while (b != 0) {
        int sum = a ^ b;
        int carry = (a & b) << 1;
        a = sum;
        b = carry;
    }

    return a;
}

} // namespace solution2

TEST_CASE("17-01", "[17-01]") {
    srand(time(nullptr));
    for (int i = 0; i < 10; ++i) {
        int a = rand();
        int b = rand();
        REQUIRE((a + b) == solution2::add(a, b));
    }
}

} // ex_17_01