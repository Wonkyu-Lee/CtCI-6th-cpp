//
// Created by blazeq on 2017. 11. 9..
//
#include <vector>
#include "catch.hpp"

namespace ex_10_01 {

using namespace std;

void mergeBToA(int A[], int aLen, int B[], int bLen) {
    int len = aLen + bLen;
    int a = aLen - 1;
    int b = bLen - 1;
    for (int i = len - 1; 0 <= i; --i) {
        if (0 <= a && 0 <= b) {
            if (A[a] >= B[b]) {
                A[i] = A[a--];
            } else {
                A[i] = B[b--];
            }
        } else if (0 <= a) {
            A[i] = A[a--];
        } else {
            B[i] = B[b--];
        }
    }
}

TEST_CASE("10-01", "[10-01]") {
    const int aLen = 5;
    const int bLen = 4;
    int A[9] = {1, 3, 5, 7, 9};
    int B[4] = {2, 4, 6, 8};

    mergeBToA(A, aLen, B, bLen);

    printf("merged: ");
    for (int i = 0; i < aLen + bLen; ++i) {
        printf("%d, ", A[i]);
    }
    printf("\n");
}

} // namespace ex_10_01