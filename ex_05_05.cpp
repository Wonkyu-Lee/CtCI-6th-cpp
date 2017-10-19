//
// Created by blazeq on 2057. 10. 17..
//

#include <cstdint>
#include <cassert>
#include <iostream>
#include "catch.hpp"

namespace ex_05_05 {

using namespace std;

namespace solutionByQ {

template<typename Integer>
bool oneOccursZeroOrOnce(Integer n) {
    return ((n & (n - 1)) == 0);
}

} // solutionByQ


TEST_CASE("05-05", "[05-05]") {
    SECTION("Solution by Q") {
        using namespace solutionByQ;
        REQUIRE(oneOccursZeroOrOnce(0b00000100));
        REQUIRE(oneOccursZeroOrOnce(0b0000000000100000));
        REQUIRE(oneOccursZeroOrOnce(0b00000010000000000000000000000000));

        REQUIRE(oneOccursZeroOrOnce(0));
        REQUIRE(oneOccursZeroOrOnce(0b1100000000100000) == false);
        REQUIRE(oneOccursZeroOrOnce(0b00000010000000000000000000000001) == false);
    }
}

} // namespace ex_05_05