//
// Created by blazeq on 2017. 10. 23..
//

#include <cstdint>
#include <cassert>
#include <iostream>
#include "catch.hpp"

namespace ex_06_07 {

using namespace std;

float averageBoyCount(int childCountUpperBound) {
    float average = 0;
    for (int i = 1; i <= childCountUpperBound; ++i) {
        average += (i - 1) * pow(0.5f, i);
    }

    return average;
}

int runOneFamily() {
    int boyCount = 0;
    while (true) {
        bool isGirl = (rand() % 2 == 1);
        if (isGirl) {
            break;
        } else {
            ++boyCount;
        }
    }

    return boyCount;
}

float simulate(int familyCount) {
    int boyCount = 0;
    int girlCount = 0;
    for (int i = 0; i < familyCount; ++i) {
        girlCount += 1;
        boyCount += runOneFamily();
    }

    return girlCount / (float)(girlCount + boyCount);
}

TEST_CASE("06-07", "[06-07]") {
    float average = averageBoyCount(100);
    printf("Average boy count: %.5f\n", average);

    float girlsToBoysRatio = simulate(10000);
    printf("Girls to boys ratio: %.5f\n", girlsToBoysRatio);
}

} // namespace ex_06_07