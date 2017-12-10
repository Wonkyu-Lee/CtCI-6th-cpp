//
// Created by blazeq on 2017. 12. 9..
//

#include "catch.hpp"
#include <iostream>

namespace ex_17_06 {

using namespace std;

namespace solution1 {

int count2sOf(int x) {
    int count = 0;
    while (x > 0) {
        if (x % 10 == 2)
            ++count;
        x /= 10;
    }
    return count;
}

int count2sInRange(int n) {
    int count = 0;
    for (int i = 2; i <= n; ++i) {
        count += count2sOf(i);
    }

    return count;
}

} // namespace solution1

namespace solution2 {

int digitCount(int n) {
    int k = 0;
    while (n > 0) {
        n /= 10;
        ++k;
    }
    return k;
}

int count2sInDigit(int n, int d) {
    int powOf10 = pow(10, d);
    int nextPowOf10 = powOf10 * 10;
    int digit = (n / powOf10) % 10;

    int roundDown = n - (n % nextPowOf10);
    int roundUp = roundDown + nextPowOf10;

    if (digit < 2) {
        return roundDown / 10;
    } else if (digit > 2) {
        return roundUp / 10;
    } else {
        return (roundDown / 10) + (n % powOf10) + 1;
    }
}

int count2sInRange(int n) {
    int count = 0;
    int digits = digitCount(n);
    for (int d = 0; d < digits; ++d) {
        count += count2sInDigit(n, d);
    }
    return count;
}

} // namespace solution2


TEST_CASE("17-06", "[17-06]") {
    {
        REQUIRE((solution1::count2sInRange(65535) == solution2::count2sInRange(65535)));
    }
}

} // namespace ex_17_06