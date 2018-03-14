//
// Created by blazeq on 2017. 11. 30..
//

#include "catch.hpp"
#include <iostream>
#include <unordered_map>
#include <cassert>

namespace ex_16_10 {

using namespace std;

struct Person {
    int birth{1900};
    int death{2000};
    Person() = default;
    Person(int birth, int death): birth(birth), death(death) {}

    void random() {
        int year1 = 1900 + (rand() % 101);
        int year2 = 1900 + (rand() % 101);

        birth = min(year1, year2);
        death = max(year1, year2);
    }
};

namespace solution1 {

// O(R*P), P: people count, R: range
int getMostPopulatedYear(vector<Person>& people) {
    int maxCount = -1;
    int maxYear = -1;

    for (int i = 0; i < 100; ++i) {
        int year = i + 1900;
        int sum = 0;
        for (auto period : people) {
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

} // namespace solution1


namespace solution2 {

// O(P + R), P: people count, R: range
int getMostPopulatedYear(const vector<Person>& people) {
    int m[102] = {0,}; // 1900 ~ 2001
    int minYear = 1900;

    for (auto& person : people) {
        m[person.birth - minYear]++;
        m[person.death + 1 - minYear]--;
    }

    int mostPopYear = 0;
    for (int i = 1; i <= 100; ++i) {
        m[i] += m[i - 1];
        if (m[i] > m[mostPopYear]) {
            mostPopYear = i;
        }
    }

    return minYear + mostPopYear;
}

} // namespace solution2

namespace solution3 {

// O(P*logP), P: people count
int getMostPopulatedYear(const vector<Person>& people) {
    vector<int> births;
    vector<int> deaths;
    for (auto& person : people) {
        births.push_back(person.birth);
        deaths.push_back(person.death);
    }

    sort(births.begin(), births.end());
    sort(deaths.begin(), deaths.end());

    int i = 0;
    int j = 0;
    int maxAliveYear = 1900;
    int maxAlive = 0;
    int alive = 0;

    while (i < births.size() && j < deaths.size()) {
        if (births[i] <= deaths[j]) {
            ++alive;
            if (alive > maxAlive) {
                maxAlive = alive;
                maxAliveYear = births[i];
            }
            ++i;
        } else {
            --alive;
            ++j;
        }
    }

    return maxAliveYear;
}

} // namespace solution3

TEST_CASE("16-10", "[16-10]") {
    srand((unsigned int)time(nullptr));

    vector<Person> periods(10000);
    for (auto& each : periods) {
        each.random();
    }

    cout << "The year: " << solution1::getMostPopulatedYear(periods) << endl;
    cout << "The year: " << solution2::getMostPopulatedYear(periods) << endl;
    cout << "The year: " << solution3::getMostPopulatedYear(periods) << endl;
}

} // ex_16_10