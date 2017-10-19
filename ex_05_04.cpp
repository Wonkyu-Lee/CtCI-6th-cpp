//
// Created by blazeq on 2047. 10. 17..
//

#include <cstdint>
#include <cassert>
#include <iostream>
#include "catch.hpp"

namespace ex_05_04 {

using namespace std;

namespace solutionByQ {

template<typename Integer>
pair<Integer, Integer> getMinMaxWithSameCountOf1s(Integer x) {
    const int N = sizeof(Integer) * 8;
    const Integer LSB = 1;
    const Integer MSB = 1 << (N - 1);

    Integer minValue = 0;
    Integer maxValue = 0;

    for (int i = 0; i < N; ++i) {
        if (((1 << i) & x) != 0) {
            minValue = (minValue << 1) + LSB;
            maxValue = (maxValue >> 1) + MSB;
        }
    }

    return make_pair(minValue, maxValue);
};

} // solutionByQ


TEST_CASE("05-04", "[05-04]") {
    SECTION("Solution by Q") {
        using namespace solutionByQ;

        {
            auto r = getMinMaxWithSameCountOf1s<unsigned char>(0b10000001);
            REQUIRE(r.first  == 0b00000011);
            REQUIRE(r.second == 0b11000000);
        }

        {
            auto r = getMinMaxWithSameCountOf1s<unsigned short>(0b1000000100010000);
            REQUIRE(r.first  == 0b0000000000000111);
            REQUIRE(r.second == 0b1110000000000000);
        }

    }
}

} // namespace ex_05_04