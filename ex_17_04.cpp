//
// Created by blazeq on 2017. 12. 8..
//

#include "catch.hpp"
#include <vector>
#include <iostream>
#include <unordered_set>

namespace ex_17_04 {

using namespace std;

namespace solution {

bool isSet(int x, int column) {
    return  (x & (1 << column)) != 0;
}

int findMissing(const vector<int>& array, int column) {
    if (column >= 32) {
        return 0;
    }

    vector<int> oneBits; oneBits.reserve(array.size()/2);
    vector<int> zeroBits; zeroBits.reserve(array.size()/2);

    for (auto v : array) {
        if (isSet(v, column)) {
            oneBits.push_back(v);
        } else {
            zeroBits.push_back(v);
        }
    }

    if (zeroBits.size() <= oneBits.size()) {
        int v = findMissing(zeroBits, column + 1);
        return (v << 1) | 0;
    } else {
        int v = findMissing(oneBits, column + 1);
        return (v << 1) | 1;
    }
}

int findMissing(const vector<int>& array) {
    return findMissing(array, 0);
}

} // namespace solution


vector<int> makeProblem(int n, int& missing) {
    auto shuffle = [](vector<int>& array) {
        for (size_t i = 1; i < array.size(); ++i) {
            size_t k = random() % (i + 1);
            swap(array[k], array[i]);
        }
    };

    vector<int> array(n);
    missing = rand() % n;

    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (k == missing) {
            ++k;
        }
        array[i] = k++;
    }
    shuffle(array);

    for (auto i : array) {
        cout << i << " ";
    }
    cout << endl;

    return array;
}


TEST_CASE("17-04", "[17-04]") {
    srand((unsigned)time(nullptr));

    for (int i = 0; i < 5; ++i) {
        int missing;
        vector<int> array = makeProblem(5, missing);
        REQUIRE(solution::findMissing(array) == missing);
    }
}

} // namespace ex_17_04