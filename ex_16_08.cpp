//
// Created by blazeq on 2017. 11. 30..
//
#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include "catch.hpp"

namespace ex_16_08 {

using namespace std;

string readNumber(int n) {
    if (n == 0) {
        return "Zero";
    }

    int interval[4] = {0,};
    for (int i = 3; 0 <= i; --i) {
        interval[i] = n % 1000;
        n /= 1000;
    }

    const string bigs[] = {"Billion", "Million", "Thousand", ""};
    const string teens[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    const string tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

    list<string> words;
    for (int i = 0; i < 4; ++i) {
        if (interval[i] == 0)
            continue;

        int h = interval[i] / 100;
        int r = interval[i] % 100;

        if (h > 0) {
            words.push_back(teens[h]);
            words.push_back("Hundred");
        }

        if (r < 20) {
            words.push_back(teens[r]);
        } else {
            words.push_back(tens[r / 10]);
            words.push_back(teens[r % 10]);
        }

        words.push_back(bigs[i]);
    }

    ostringstream out;
    for (auto word : words) {
        out << word << " ";
    }

    string str = out.str();
    if (str.size() > 0) {
        return str.substr(0, str.length() - 2); // TODO: 확인. 마지막 space trim!
    } else {
        return str;
    }
}

TEST_CASE("16-08", "[16-08]") {
    REQUIRE(readNumber(0) == "Zero");
    REQUIRE(readNumber(7) == "Seven");
    REQUIRE(readNumber(543) == "Five Hundred Forty Three");
    REQUIRE(readNumber(11512) == "Eleven Thousand Five Hundred Twelve");
    REQUIRE(readNumber(2104712638) == "Two Billion One Hundred Four Million Seven Hundred Twelve Thousand Six Hundred Thirty Eight");
}


} // namespace ex_16_08