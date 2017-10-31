//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"

namespace ex_08_05 {

using namespace std;

int multiplyRecurse(int smaller, int larger) {
    if (smaller == 0)
        return 0;

    if (smaller == 1)
        return larger;

    int leftSide = multiplyRecurse(smaller >> 1, larger);
    int rightSide = (smaller % 2 == 0) ? leftSide : leftSide + larger;
    return leftSide + rightSide;
}

int multiply(int a, int b) {
    int smaller, larger;
    if (a <= b) {
        smaller = a;
        larger = b;
    } else {
        smaller = b;
        larger = a;
    }

    return multiplyRecurse(smaller, larger);
}

TEST_CASE("08-05", "[08-05]") {
    REQUIRE(multiply(35, 21) == 35 * 21);
}

} // namespace ex_08_05