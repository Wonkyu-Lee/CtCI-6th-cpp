//
// Created by blazeq on 2017. 12. 8..
//

#include <iostream>
#include <vector>
#include "catch.hpp"

namespace ex_17_03 {

using namespace std;

namespace solution1 {

void pickMRecurse(vector<int>& array, size_t m, size_t i, vector<int>& result) {
    if (i == m - 1) {
        return;
    }

    pickMRecurse(array, m, i - 1, result);

    size_t k = rand() % (i + 1);
    if (k < m) {
        result[k] = array[i];
    }
}

vector<int> pickM(vector<int>& array, size_t m) {
    vector<int> result(m);
    for (size_t i = 0; i < m; ++i) {
        result[i] = array[i];
    }

    pickMRecurse(array, m, array.size() - 1, result);
    return result;
}

} // namespace solution1

namespace solution2 {

vector<int> pickM(vector<int>& array, size_t m) {
    vector<int> result(m);
    for (size_t i = 0; i < m; ++i) {
        result[i] = array[i];
    }

    for (size_t i = m; i < array.size(); ++i) {
        size_t k = random() % (i + 1);
        if (k < m) {
            result[k] = array[i];
        }
    }

    return result;
}

} // namespace solution2

TEST_CASE("17-03", "[17-03]") {
    srand((unsigned)time(nullptr));

    vector<int> array(10);
    for (int i = 0; i < 10; ++i) {
        array[i] = i;
    }

    for (int k = 0; k < 20; ++k) {
        auto result = solution2::pickM(array, 3);
        for (int i = 0; i < 3; ++i) {
            cout << result[i] << " ";
        }
        cout << endl;
    }
}

} // namespace ex_17_03