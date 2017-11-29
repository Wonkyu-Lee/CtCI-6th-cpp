//
// Created by blazeq on 2017. 11. 30..
//

#include "catch.hpp"

namespace ex_16_06 {

int findPrevIndex(int value, int arr[], int p, int r) {
    if (p > r) {
        return p - 1;
    }

    int q = (p + r) / 2;
    if (value < arr[q]) {
        return findPrevIndex(value, arr, p, q - 1);
    } else if (arr[q] < value) {
        return findPrevIndex(value, arr, q + 1, r);
    } else {
        return q;
    }
}

int calcMinDiff(int* A, int nA, int* B, int nB) {
    int* L, nL;
    int* S, nS;
    if (nA >= nB) {
        L = A; nL = nA;
        S = B; nS = nB;
    } else {
        L = B; nL = nB;
        S = A; nS = nA;
    }

    int minDiff = ~(1 << 31); // max int
    std::sort(S, S + nS);

    for (int i = 0; i < nL; ++i) {
        int v = L[i];

        int prev = findPrevIndex(v, S, 0, nS - 1);
        int diff = 0;
        if (prev == -1) {
            diff = S[0] - v;
        } else if (prev == nS - 1) {
            diff = v - S[prev];
        } else {
            int next = prev + 1;
            diff = std::min(v - S[prev], S[next] - v);
        }

        if (diff < minDiff) {
            minDiff = diff;
        }
    }

    return minDiff;

}

TEST_CASE("16-06", "[16-06]") {
    {
        int A[] = {1, 3, 15, 11, 2};
        int nA = sizeof(A) / sizeof(int);

        int B[] = {23, 127, 235, 19, 8};
        int nB = sizeof(B) / sizeof(int);

        REQUIRE(calcMinDiff(A, nA, B, nB) == 3);
    }

    {
        int A[] = {199, 1, 3, 15, 234, 11, 2};
        int nA = sizeof(A) / sizeof(int);

        int B[] = {23, 127, 235, 19, 8, 160, 785, 200};
        int nB = sizeof(B) / sizeof(int);

        REQUIRE(calcMinDiff(A, nA, B, nB) == 1);
    }
}

} // namespace ex_16_06