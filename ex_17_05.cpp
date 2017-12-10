//
// Created by blazeq on 2017. 12. 9..
//

#include "catch.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>

namespace ex_17_05 {

using namespace std;

namespace solution1 {

bool hasEqualDigitsAlphabets(const vector<char>& array, int start, int end) {
    int delta = 0;
    for (int i = 0; i <= end; ++i) {
        if (isdigit(array[i]))
            delta++;
        else if (isalpha(array[i]))
            delta--;
    }
    return delta == 0;
}

vector<char> findLongestSubsequence(const vector<char>& array) {
    vector<char> result;
    for (int len = array.size(); 1 < len; --len) {
        for (int i = 0; i + len - 1 < array.size(); ++i) {
            if (hasEqualDigitsAlphabets(array, i, i + len - 1)) {
                int start = i;
                for (int k = 0; k < len; ++k) {
                    result.push_back(array[start++]);
                }
                return result;
            }
        }
    }
    return result;
}

} // namespace solution1

namespace solution2 {

vector<char> findLongestSubsequence(const vector<char>& array) {
    pair<int, int> longest(-1, -1);

    // get deltas(# of digits - # of alphabets)
    vector<int> deltas(array.size());
    int delta = 0;
    for (int i = 0; i < array.size(); ++i) {
        if (isdigit(array[i])) {
            delta++;
        } else if (isalpha(array[i])) {
            delta--;
        }
        deltas[i] = delta;
        if (delta == 0) {
            longest.first = -1;
            longest.second = i;
        }
    }

    // find the longest range between same delta values
    unordered_map<int, int> ranges;
    for (int i = 0; i < deltas.size(); ++i) {
        auto found = ranges.find(deltas[i]);
        if (found == ranges.end()) {
            ranges[deltas[i]] = i;
        } else {
            int longestLen = longest.second - longest.first;
            int start = found->second;
            if (i - start > longestLen) {
                longest.first = start;
                longest.second = i;
            }
        }
    }

    // extract the longest subsequence
    vector<char> result;
    result.reserve(longest.second - longest.first + 1);
    if (longest.second == -1) {
        return result;
    }

    for (int i = longest.first + 1; i <= longest.second; ++i) {
        result.push_back(array[i]);
    }
    return result;
}

} // namespace solution2

TEST_CASE("17-05", "[17-05]") {
    SECTION("test1") {
        string input = "aaaa11a11a11aa1aa1aaaaa";
        vector<char> array(input.begin(), input.end());
        auto r = solution2::findLongestSubsequence(array);
        cout <<"subsequence: ";
        for (auto ch : r) {
            cout << ch;
        }
        cout << endl;
    }

    SECTION("test2") {
        string input = "1aaa11";
        vector<char> array(input.begin(), input.end());
        auto r = solution2::findLongestSubsequence(array);
        cout <<"subsequence: ";
        for (auto ch : r) {
            cout << ch;
        }
        cout << endl;
    }
}

} // namespace ex_17_05