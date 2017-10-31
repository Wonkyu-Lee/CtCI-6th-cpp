//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <functional>
#include <vector>

namespace ex_08_04 {

using namespace std;

using Callback = function<void(int[], int)>;

void combRecurse(int arr[], int start, int end, int r, int result[], int index, Callback cb) {
    if (index == r) {
        cb(result, r);
        return;
    }

    for (int i = start; (i <= end) && (r - index <= end - i + 1); ++i) {
        result[index] = arr[i];
        combRecurse(arr, i + 1, end, r, result, index + 1, cb);
    }
}

void combination(int arr[], int n, int r, Callback cb) {
    int result[r];
    combRecurse(arr, 0, n - 1, r, result, 0, cb);
}

void getAllSubsets(int arr[], int n, vector<vector<int>>& result) {
    result.clear();
    for (int i = 0; i <= n; ++i) {
        combination(arr, n, i, [&](int combination[], int k) {
            vector<int> subset;
            for (int j = 0; j < k; ++j)
                subset.push_back(combination[j]);

            result.push_back(subset);
        });

    }
}

TEST_CASE("08-04", "[08-04]") {

    int arr[] = {1, 2, 3, 4, 5};
    vector<vector<int>> result;
    getAllSubsets(arr, 5, result);

    for (auto& each : result) {
        if (each.empty()) {
            printf("{}\n");
        } else {
            printf("{");
            for (auto value : each) {
                printf("%d, ", value);
            }
            printf("\b\b}\n");
        }
    }
}

} // namespace ex_08_04