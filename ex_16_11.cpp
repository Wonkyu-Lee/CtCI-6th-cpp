//
// Created by blazeq on 2017. 11. 30..
//

#include <iostream>
#include <set>
#include "catch.hpp"

namespace ex_16_11 {

using namespace std;
using HashSet = set<int>;

HashSet getAllLengthsOfDivingBoards(int shorter, int longer, int k) {
    HashSet lengths;
    for (int i = 0; i <= k; ++i) {
        int nS = i;
        int nL = k - 1;
        lengths.insert(shorter * nS + longer * nL);
    }

    return lengths;
}

TEST_CASE("16-11", "[16-11]") {
    auto lengths = getAllLengthsOfDivingBoards(3, 5, 10);
    for (auto each : lengths) {
        cout << each << " ";
    }
    cout << endl;
}

} // namespace ex_16_11