//
// Created by blazeq on 2017. 11. 9..
//

#include "catch.hpp"
#include <unordered_map>
#include <list>

namespace ex_10_02 {

using namespace std;

string sortedByChar(const string& s) {
    string sorted = s;
    std::sort(sorted.begin(), sorted.end());
    return sorted;
}

void groupAnagrams(string str[], int n) {
    unordered_map<string, list<string>> hash;
    for (int i = 0; i < n; ++i) {
        hash[sortedByChar(str[i])].push_back(str[i]);
    }

    int j = 0;
    for (auto& l : hash) {
        for (auto i : l.second) {
            str[j++] = i;
        }
    }
}

TEST_CASE("10-02", "[10-02]") {
    string array[] = {"dusty", "inch", "rat", "below", "cider", "tar", "study", "chin", "cried", "elbow"};

    int n = sizeof(array)/sizeof(string);
    groupAnagrams(array, n);

    printf("anagram grouped: ");
    for (int i = 0; i < n; ++i) {
        printf("%s, ", array[i].c_str());
    }
    printf("\n");
}

} // namespace ex_10_02