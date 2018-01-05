//
// Created by blazeq on 2018. 1. 3..
//

#include "catch.hpp"
#include <iostream>

namespace ex_17_09 {

using namespace std;

int kth(int prime[], int m, int k) {
    if (m == 0 || k == 0) return 0;

    int dp[k];
    dp[0] = 1;
    int next[m];
    int index[m];
    for (int i = 0; i < m; ++i) {
        next[i] = prime[i];
        index[i] = 0;
    }

    for (int i = 1; i < k; ++i) {
        int minNext = next[0];
        for (int j = 1; j < m; ++j) {
            if (next[j] < minNext) {
                minNext = next[j];
            }
        }
        dp[i] = minNext;
        for (int j = 0; j < m; ++j) {
            if (next[j] == minNext) {
                index[j]++;
                next[j] = prime[j] * dp[index[j]];
            }
        }
    }

    return dp[k - 1];
}

int kth(int k) {
    int m = 3;
    int prime[] = {3, 5, 7};
    return kth(prime, m, k);
}

TEST_CASE("17-09", "[17-09]") {
    for (int i = 1; i < 10; ++i) {
        cout << kth(i) << " ";
    }
    cout << endl;
}

} // namespace ex_17_09