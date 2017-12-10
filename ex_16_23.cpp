//
// Created by blazeq on 2017. 12. 4..
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "catch.hpp"
#include <map>

namespace ex_16_23 {

using namespace std;

class Random {
public:
    Random() {
        srand((unsigned int)time(nullptr));
    }

    int rand5() {
        return rand() % 5;
    }

    int rand7() {
        while (true) {
            int r = rand5() * 5 + rand5();
            if (r < 21) {
                return r % 7;
            }
        }
    }

    int rand7_2() {
        while (true) {
            int r1 = rand5() * 2;
            int r2 = rand5();
            if (r2 == 4) {
                continue;
            }

            int r = r1 + (r2 % 2);
            if (r < 7) {
                return r;
            }
        }
    }
};

TEST_CASE("16-23", "[16-23]") {

    map<int, int> counts;

    Random random;

    for (int i = 0; i < 1000; ++i) {
        int x = random.rand7_2();
        counts[x]++;
    }

    for (auto each : counts) {
        cout << each.first << ": " << each.second << endl;
    }
}

} // namespace ex_16_23