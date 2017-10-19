//
// Created by blazeq on 2017. 10. 17..
//

#include <cstdint>
#include <cassert>
#include <iostream>
#include "catch.hpp"

namespace ex_05_01 {

using namespace std;

namespace solutionByQ {

int insertMtoN(uint32_t m, uint32_t n, int i, int j) {
    uint32_t mask = 1;
    mask = ~(((mask << (j - i + 1)) - 1) << i) ;
    return (n & mask) | (m << i);
}

} // solutionByQ


TEST_CASE("05-01", "[05-01]") {
    SECTION("Solution by Q") {
        using namespace solutionByQ;
        REQUIRE(insertMtoN(0b10011, 0b10000000000, 2, 6) == 0b10001001100);
    }
}

} // namespace ex_05_01