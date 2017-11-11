//
// Created by blazeq on 2017. 11. 9..
//

#include "catch.hpp"

namespace ex_10_05 {

using namespace std;

int findIndexOfValue(const string arr[], int n, const string& x) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid].empty()) {
            int l = mid - 1;
            int r = mid + 1;
            while (true) {
                if (l < low && high < r) {
                    return -1;
                }

                if (low <= l && !arr[l].empty()) {
                    mid = l;
                    break;
                }

                if (r <= high && !arr[r].empty()) {
                    mid = r;
                    break;
                }
                --l;
                ++r;
            }
        }

        if (x < arr[mid]) {
            high = mid - 1;
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

TEST_CASE("10-05", "[10-05]") {
    string arr[] = { "at", "", "", "", "ball", "", "", "car", "", "", "dad", "", "" };

    int n = sizeof(arr) / sizeof(string);

    for (int i = 0; i < n; ++i) {
        if (!arr[i].empty())
            REQUIRE(findIndexOfValue(arr, n, arr[i]) == i);
    }

    REQUIRE(findIndexOfValue(arr, n , "an") == -1);
    REQUIRE(findIndexOfValue(arr, n , "noexist") == -1);
}

} // namespace ex_10_05