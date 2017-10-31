//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <functional>

namespace ex_08_07 {

using namespace std;

using Callback = function<void(char*)>;

void permutation(char* text, int start, Callback cb) {
    int l = strlen(text);
    if (start == l) {
        cb(text);
        return;
    }

    unordered_set<char> swapped;
    for (int i = start; i < l; ++i) {
        if (swapped.find(text[i]) != swapped.end()) {
            continue;
        }

        swapped.insert(text[i]);

        swap(text[start], text[i]);
        permutation(text, start + 1, cb);
        swap(text[start], text[i]);
    }
}

void permutation(char* text, Callback cb) {
    permutation(text, 0, cb);
}

int factorial(int n) {
    if (n <= 1)
        return 1;

    int t = 1;
    for (int i = 2; i <= n; ++i) {
        t *= i;
    }

    return t;
}

int countPermutations(char* text) {
    unordered_map<char, int> m;
    int l = strlen(text);
    for (int i = 0; i < l; ++i) {
        ++m[text[i]];
    }

    int count = factorial(l);
    for (auto each : m) {
        count /= factorial(each.second);
    }

    return count;
}

TEST_CASE("08-07", "[08-07]") {
    char text[256] = "cabda";
    int count = 0;
    permutation(text, [&](char* r) {
        cout << r << endl;
        ++count;
    });

    printf("# permutations: %d == %d\n", countPermutations(text), count);
}

} // namespace ex_08_07