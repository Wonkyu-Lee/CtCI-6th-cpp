//
// Created by blazeq on 2018. 1. 6..
//

#include "catch.hpp"
#include <iostream>
#include <vector>

namespace ex_17_14 {

using namespace std;

int partition(int A[], int p, int r) {
    int x = A[r];
    int i = p - 1;
    int j = p;
    while (j < r) {
        if (x < A[j]) {
            ++j;
        } else {
            swap(A[i + 1], A[j]);
            ++i;
            ++j;
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

int select(int A[], int p, int r, int k) {
    if (p > r) return -1; // 밖에서 k값 체크해주면 여기서 체크 필요 없다.

    int q = partition(A, p, r);
    if (k < q) {
        return select(A, p, q - 1, k);
    } else if (k > q) {
        return select(A, q + 1, r, k);
    } else {
        return A[q];
    }
}

vector<int> minKNumbers(int A[], int n, int k) {
    if (k <= 0 || n < k) return vector<int>();

    int B[n];
    copy(A, A + n, B);
    select(B, 0, n - 1, k - 1);
    vector<int> result(k);
    copy(B, B + k, result.begin());
    return result;
}


TEST_CASE("17-14", "[17-14]") {
    int A[] = {4, 1, 5, 3, 4, 3, 2, 4};
    int n = 8;

    auto printMinKNumbers = [&](int k) {
        vector<int> r = minKNumbers(A, n, k);
        for (auto e : r) {
            cout << e << " ";
        }
        cout << endl;
    };

    for (int i = 1; i <= 8; ++i) {
        printMinKNumbers(i);
    }
}

} // namespace ex_17_14