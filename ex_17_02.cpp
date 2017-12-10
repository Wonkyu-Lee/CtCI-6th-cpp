//
// Created by blazeq on 2017. 12. 8..
//

#include "catch.hpp"
#include <iostream>
#include <list>

namespace ex_17_02 {

using namespace std;

namespace mine {

void shuffle(int array[], int n) {
    list<int> values;
    for (size_t i = 0; i < n; ++i) {
        values.push_back(array[i]);
    }

    for (size_t i = 0; i < n; ++i) {
        size_t toRemove = rand() % values.size();
        auto it = values.begin();
        for (size_t j = 0; j < toRemove; ++j) {
            ++it;
        }
        array[i] = *it;
        values.erase(it);
    }
}

} // namespace mine



namespace solution1 {

void shuffle(int array[], int n) {
    if (n == 0)
        return;

    shuffle(array, n - 1);
    int i = rand() % n;
    swap(array[i], array[n - 1]);
}

} // namespace solution1

namespace solution2 {

void shuffle(int array[], int n) {
    for (int k = 2; k <= n; ++k) {
        int i = rand() % k;
        swap(array[i], array[k - 1]);
    }
}

} // namespace solution2

TEST_CASE("17-02", "[17-02]") {
    int card[52] = {0,};
    for (int i = 0; i < 52; ++i) {
        card[i] = i;
    }
    solution2::shuffle(card, 52);
    for (int i = 0; i < 52; ++i) {
        cout << card[i] << " ";
    }
    cout << endl;
}

} // ex_17_02