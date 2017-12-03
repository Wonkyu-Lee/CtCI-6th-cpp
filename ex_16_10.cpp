//
// Created by blazeq on 2017. 11. 30..
//

#include "catch.hpp"
#include <iostream>

namespace ex_16_10 {

using namespace std;

struct Period {
    int birth{1900};
    int death{2000};
    Period() = default;
    Period(int birth, int death): birth(birth), death(death) {}

    void random() {
        birth = 1900 +(rand() % 101);
        int age = rand() % 120; // TODO: make normal distribution
        death = birth + age;
    }
};

int getMostPopulatedYear(vector<Period>& periods) {
    int maxCount = -1;
    int maxYear = -1;

    for (int i = 0; i < 100; ++i) {
        int year = i + 1900;
        int sum = 0;
        for (auto period : periods) {
            if (period.birth <= year && year <= period.death) {
                ++sum;
            }
        }
        if (sum > maxCount) {
            maxCount = sum;
            maxYear = year;
        }
    }

    return maxYear;
}


TEST_CASE("16-10", "[16-10]") {
    srand((unsigned int)time(nullptr));

    vector<Period> periods(10000);
    for (auto& each : periods) {
        each.random();
    }

    cout << "The year: " << getMostPopulatedYear(periods) << endl;
}

} // ex_16_10