//
// Created by blazeq on 2017. 12. 4..
//

#include "catch.hpp"
#include <iostream>

namespace ex_16_21 {

using namespace std;

bool getPair(const vector<int>& a, const vector<int>& b, pair<int, int>& result) {
    int aSum = 0;
    int bSum = 0;
    for (auto& each : a) {
        aSum += each;
    }
    for (auto& each : b) {
        bSum += each;
    }
    set<int> aSet(a.begin(), a.end());
    set<int> bSet(b.begin(), b.end());

    for (auto& ae : aSet) {
        for (auto& be : bSet) {
            if (aSum - ae + be == bSum - be + ae) {
                result.first = ae;
                result.second = be;
                return true;
            }
        }
    }

    return false;
};

TEST_CASE("16-21", "[16-21]") {
    pair<int, int> r;
    if (getPair({4, 1, 2, 1, 1, 2}, {3, 6, 3, 3}, r)) {
        printf("(%d, %d)\n", r.first, r.second);
    }
}

} // namespace ex_16_21