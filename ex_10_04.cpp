//
// Created by blazeq on 2017. 11. 9..
//

#include "catch.hpp"

namespace ex_10_04 {

using namespace std;

class Listy {
private:
    int len;
    vector<int> values;

public:
    template<typename ForwardIterator>
    Listy(ForwardIterator begin, ForwardIterator end): values(begin, end) {
        len = (int)values.size();
    }

    int elementAt(int i) {
        if (i < 0 || len <= i) {
            return -1;
        }

        return values[i];
    }
};

int binarySearch(Listy& listy, int p, int r, int x) {
    if (p > r)
        return -1;

    int q = (p + r) / 2;
    if (x == listy.elementAt(q)) {
        return q;
    }

    if (x < listy.elementAt(q)) {
        return binarySearch(listy, p, q - 1, x);
    } else {
        return binarySearch(listy, q + 1, r, x);
    }
}

namespace solution1 {

int findIndexOfValue(Listy& listy, int x) {
    int n = 0;
    while (listy.elementAt(n) != -1) {
        ++n;
    }

    return binarySearch(listy, 0, n - 1, x);
}

} // namespace solution1

namespace solution2 {

int findIndexOfValue(Listy& listy, int x) {
    if (listy.elementAt(0) == x) {
        return 0;
    }

    int prv = 0;
    int step = 1;
    while (true) {
        int cur = prv + step;
        int curVal = listy.elementAt(cur);
        if (curVal == -1) {
            if (step == 1)
                return -1;

            step = 1;
            continue;
        }

        if (x == curVal) {
            return cur;
        }

        if (x < curVal) {
            return binarySearch(listy, prv + 1, cur - 1, x);
        }

        prv = cur;
        step *= 2;
    }
}

} // namespace solution2

namespace solution3 {

int binarySearch_(Listy& listy, int low, int high, int x) {
    while (low <= high) {
        int mid = (low + high) / 2;
        int middle = listy.elementAt(mid);
        if (x < middle || middle == -1) {
            high = mid - 1;
        } else if (middle < x) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int findIndexOfValue(Listy& listy, int x) {
    int index = 1;
    while (listy.elementAt(index) != -1 && listy.elementAt(index) < x) {
        index *= 2;
    }

    return binarySearch_(listy, index/2, index, x);
}

} // namespace solution3

TEST_CASE("10-04", "[10-04]") {
    int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    int n = sizeof(arr)/sizeof(int);
    Listy listy(arr, arr + n);

    for (int i = 0; i < n; ++i) {
        REQUIRE(solution3::findIndexOfValue(listy, arr[i]) == i);
    }
}

} // namespace ex_10_04