//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <functional>
#include <vector>

namespace ex_08_04 {

using namespace std;

namespace solution1 {

void getAllSubsetsRecurse(int arr[], int n, vector<vector<int>>& result, int index) {
    if (index == n) {
        result.push_back(vector<int>()); // empty set
        return;
    }

    getAllSubsetsRecurse(arr, n, result, index + 1);

    vector<vector<int>> moreSubsets(result);

    for (auto& subset : moreSubsets) {
        subset.push_back(arr[index]);
    }

    result.insert(result.end(), moreSubsets.begin(), moreSubsets.end());
}

void getAllSubsets(int arr[], int n, vector<vector<int>>& result) {
    result.clear();
    getAllSubsetsRecurse(arr, n, result, 0);
}

} // namespace solution1

namespace solution2 {

void getAllSubsets(int arr[], int n, vector<vector<int>>& result) {
    result.clear();
    result.push_back(vector<int>()); // empty subset

    for (int i = 0; i < n; ++i) {
        vector<vector<int>> moreSubsets(result);

        for (auto& subset : moreSubsets) {
            subset.push_back(arr[i]);
        }

        result.insert(result.end(), moreSubsets.begin(), moreSubsets.end());
    }
}

} // namespace solution2

namespace solution3 {

void getAllSubsets(int arr[], int n, vector<vector<int>>& result) {
    auto getSubset = [&arr, &n](int bitSet, vector<int>& subset) {
        for (int i = 0; i < n; ++i) {
            if (bitSet & (1 << i)) {
                subset.push_back(arr[i]);
            }
        }
    };

    int allSet = std::pow(2, n) - 1;
    for (int bitSet = 0; bitSet <= allSet; ++bitSet) {
        result.push_back(vector<int>());
        auto& subset = result.back();
        getSubset(bitSet, subset);
    }
}

} // namespace solution3

namespace solution4 {

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
} // namespace solution4

TEST_CASE("08-04", "[08-04]") {
    function<void(int[], int, vector<vector<int>>&)> solutions[] = {
        solution1::getAllSubsets,
        solution2::getAllSubsets,
        solution3::getAllSubsets,
        solution4::getAllSubsets
    };

    for (int i = 1; i <= 4; ++i) {
        auto getAllSubsets = solutions[i - 1];

        printf("Solution%d:\n", i);
        int arr[] = {1, 2, 3, 4, 5};
        vector<vector<int>> result;
        solution2::getAllSubsets(arr, 5, result);
        printf("# of all subsets = %lu\n", result.size());

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
        printf("\n");
    }
}

} // namespace ex_08_04