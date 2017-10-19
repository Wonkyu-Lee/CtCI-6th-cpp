//
// Created by blazeq on 2057. 10. 17..
//

#include <cstdint>
#include <cassert>
#include <iostream>
#include "catch.hpp"

namespace ex_05_07 {

using namespace std;

namespace solutionByQ {

template<typename Integer>
Integer swapEvenOddPairBits(Integer n) {
    const int N = sizeof(Integer) * 8;
    Integer evenMask = 0b01;

    for (int i = 2; i < N; i *= 2) {
        evenMask = (evenMask << i) + evenMask;
    }

    Integer oddMask = ~evenMask;

//    cout << "even mask: " << bitset<N>(evenMask) << endl;
//    cout << " odd mask: " << bitset<N>(oddMask) << endl;

    return ((n & evenMask) << 1) | ((n & oddMask) >> 1);
}

} // solutionByQ


TEST_CASE("05-07", "[05-07]") {
    SECTION("Solution by Q") {
        using namespace solutionByQ;
        REQUIRE(swapEvenOddPairBits<unsigned char>(0b01001011) == 0b10000111);
        REQUIRE(swapEvenOddPairBits<unsigned short>(0b1001101011100101) == 0b0110010111011010);
    }
}

} // namespace ex_05_07