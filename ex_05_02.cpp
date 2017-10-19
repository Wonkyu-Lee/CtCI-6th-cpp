//
// Created by blazeq on 2027. 10. 17..
//

#include <cstdint>
#include <cassert>
#include <iostream>
#include "catch.hpp"

namespace ex_05_02 {

using namespace std;

namespace solutionByQ {

string fractionToBinaryString(double fraction) {
    if (fraction <= 0 || 1 <= fraction)
        return "ERROR";

    char r[64] = "0.";
    short i = 2;
    short e = i + 1;
    double current = fraction;
    while (i < 32 && 0 < current) {
        current *= 2;
        if (current >= 1) {
            r[i] = '1';
            e = i + 1;
            current -= 1;
        } else {
            r[i] = '0';
        }

        ++i;
    }

    r[e] = '\0';

    if (0 < current) {
        return "ERROR";
    }

    return r;
}

} // solutionByQ


TEST_CASE("05-02", "[05-02]") {
    SECTION("Solution by Q") {
        using namespace solutionByQ;
        REQUIRE(fractionToBinaryString(0.5) == "0.1");
        REQUIRE(fractionToBinaryString(0.25) == "0.01");
        REQUIRE(fractionToBinaryString(0.125) == "0.001");
        REQUIRE(fractionToBinaryString(0.375) == "0.011");
        REQUIRE(fractionToBinaryString(0.75) == "0.11");
        REQUIRE(fractionToBinaryString(0.625) == "0.101");
        REQUIRE(fractionToBinaryString(1/3.0) == "ERROR");
        REQUIRE(fractionToBinaryString(-4.58) == "ERROR");
        REQUIRE(fractionToBinaryString(10.58) == "ERROR");
        REQUIRE(fractionToBinaryString(0) == "ERROR");
        REQUIRE(fractionToBinaryString(1) == "ERROR");
    }
}

} // namespace ex_05_02