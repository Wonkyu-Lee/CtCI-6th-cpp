//
// Created by blazeq on 2017. 12. 4..
//

#include "catch.hpp"
#include <iostream>
#include <list>
#include <map>

namespace ex_16_24 {

using namespace std;

map<int, int> findAllPairsWithSum(const vector<int>& array, int sum) {
    map<int, int> result;
    map<int, int> counts;
    vector<bool> used(false, array.size());
    for (auto each : array) {
        counts[each]++;
    }

    for (auto each : counts) {
        int a = each.first;
        int b  = sum - a;
        if (a > b)
            break;

        auto found = counts.find(b);
        if (found == counts.end()) {
            continue;
        } else if (a == b && found->second < 2) {
            continue;
        } else {
            result.insert(make_pair(a, b));
        }
    }
    return result;
};

TEST_CASE("16-24", "[16-24]") {

    vector<int> array({-5, -4, -3, -2, -1, -1,  0, 1, 2, 2, 3, 4, 5, 5});
    {
        auto result = findAllPairsWithSum(array, 4);
        for (auto each : result) {
            printf("(%d, %d) ", each.first, each.second);
        }
    }
}

} // namespace ex_16_24
