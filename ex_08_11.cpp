//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <list>
#include <vector>

namespace ex_08_11 {

using namespace std;

enum { QUATER, DIME, NICKEL, PENNY, NUM_COINS };
const int CENTS[] = { 25, 10, 5, 1 };
const char* COIN_STR[] = { "quater", "dime", "nickel", "penny" };

void addCentsRecurs(list<vector<int>>& result, int goal, vector<int>& counts, int& total) {
    if (goal < total) {
        return;
    }

    if (goal == total) {
        result.push_back(counts);
        return;
    }

    for (int i = QUATER; i < NUM_COINS; ++i) {
        if (total + CENTS[i] <= goal) {
            ++counts[i];
            total += CENTS[i];
            addCentsRecurs(result, goal, counts, total);
            --counts[i];
            total -= CENTS[i];
        }
    }
}

void generateCents(list<vector<int>>& result, int cents) {
    result.clear();
    vector<int> counts(NUM_COINS, 0);
    int total = 0;
    addCentsRecurs(result, cents, counts, total);

    for (auto each : result) {
        for (int i = QUATER; i < NUM_COINS; ++i) {
            printf("%d %s, ", each[i], COIN_STR[i]);
        }

        printf("\b\b\n");
    }
}

TEST_CASE("08-11", "[08-11]") {
    list<vector<int>> result;
    generateCents(result, 10);
}

} // namespace ex_08_11