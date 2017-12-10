//
// Created by blazeq on 2017. 12. 4..
//

#include "catch.hpp"
#include <iostream>
#include <unordered_set>

namespace ex_16_21 {

using namespace std;

namespace solution1 {

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

} // namespace solution1

namespace solution2 {

bool getPair(const vector<int>& a, const vector<int>& b, pair<int, int>& result) {
    int aSum = 0;
    int bSum = 0;

    unordered_set<int> bSet;

    for (auto& each : a) {
        aSum += each;
    }
    for (auto& each : b) {
        bSum += each;
        bSet.insert(each);
    }

    for (auto& aEl : a) {
        int temp = bSum - aSum + 2 * aEl;
        if (temp % 2 == 0) {
            int bEl = temp / 2;
            if (bSet.find(bEl) != bSet.end()) {
                result.first = aEl;
                result.second = bEl;
                return true;
            }
        }
    }

    return false;
};

} // namespace solution2

TEST_CASE("16-21", "[16-21]") {
    pair<int, int> r;
    if (solution1::getPair({4, 1, 2, 1, 1, 2}, {3, 6, 3, 3}, r)) {
        printf("(%d, %d)\n", r.first, r.second);
    }
}

} // namespace ex_16_21