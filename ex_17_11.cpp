//
// Created by blazeq on 2018. 1. 4..
//

#include "catch.hpp"
#include <iostream>
#include <unordered_map>

namespace ex_17_11 {

using namespace std;

class LocationPair {

public:
    int p1{-1};
    int p2{-1};

    LocationPair() = default;
    LocationPair(int p1, int p2): p1(p1), p2(p2) {}

    int distance() const {
        return abs(p1 - p2);
    }

    bool valid() const {
        return p1 != -1 && p2 != -1;
    }

    void updateIfShort(const LocationPair& other) {
        if (!other.valid()) return;
        if (!valid() || other.distance() < distance()) {
            *this = other;
        }
    }
};

namespace solution1 {

int findBestMin(const vector<string>& words, const string& word1, const string word2)
{
    LocationPair bestMin;
    LocationPair current;
    for (int i = 0; i < words.size(); ++i) {
        const string& word = words[i];

        if (word == word1) {
            current.p1 = i;
        } else if (word == word2) {
            current.p2 = i;
        } else {
            continue;
        }

        bestMin.updateIfShort(current);
    }
    return bestMin.distance();
}

} // namespace solution1

namespace solution2 {

using WordLocMap = unordered_map<string, vector<int>>;

void getWordLocations(const vector<string>& words, WordLocMap& wordLocMap) {
    for (int i = 0; i < words.size(); ++i) {
        auto& word = words[i];
        wordLocMap[word].push_back(i);
    }
}

int findBestMin(const vector<string>& words, const string& word1, const string word2) {
    WordLocMap wordLocMap;
    getWordLocations(words, wordLocMap);

    auto found1 = wordLocMap.find(word1);
    if (found1 == wordLocMap.end())
        return -1;

    auto found2 = wordLocMap.find(word2);
    if (found2 == wordLocMap.end())
        return -1;

    auto& locs1 = found1->second;
    auto& locs2 = found2->second;

    int i1 = 0;
    int i2 = 0;

    LocationPair bestMin(locs1[0], locs2[0]);
    while (i1 < locs1.size() && i2 < locs2.size()) {
        int p1 = locs1[i1];
        int p2 = locs2[i2];
        if (p1 < p2) {
            ++i1;
        } else {
            ++i2;
        }
        bestMin.updateIfShort(LocationPair(p1, p2));
    }

    return bestMin.distance();
}

} // namespace solution2


TEST_CASE("17-11", "[17-11]") {
    vector<string> words({"hello", "hi", "nice", "world", "google", "samsung", "hello", "apple", "world"});
    REQUIRE(solution1::findBestMin(words, "hello", "world") == 2); // O(n), n == word count
    REQUIRE(solution2::findBestMin(words, "hello", "world") == 2); // max {O(n), O(a + b)}
}

} // namespace ex_17_11