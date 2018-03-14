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

namespace solution1 {

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

} // namespace solution1


namespace solution2 {

class IntReader {
    static const string BIGS[];
    static const string TENS[];
    static const string SMALLS[];

public:
    static string read(int n) {
        if (n == 0)
            return SMALLS[0];

        list<string> parts;
        bool negative = n < 0;
        if (negative) {
            n = -n;
        }

        int current = n;
        int i = 0;
        while (current > 0) {
            ostringstream out;
            int chunk = current % 1000;
            if (chunk > 0) {
                out << readChunk(chunk);
                if (i > 0) {
                    out << " " << BIGS[i];
                }
                parts.push_front(out.str());
            }

            current /= 1000;
            ++i;
        }

        if (negative) {
            parts.push_front("Negative");
        }

        return convert(parts);
    }

    static string readChunk(int n) {
        list<string> parts;

        if (n / 100 > 0) {
            parts.push_back(SMALLS[n / 100]);
            parts.push_back("Hundred");
            n = n % 100;
        }

        if (20 <= n) {
            parts.push_back(TENS[n / 10]);
            n = n % 10;
        }

        if (0 < n) {
            parts.push_back(SMALLS[n]);
        }

        return convert(parts);
    }

    static string convert(list<string>& parts) {
        ostringstream out;

        while (parts.size() > 1) {
            out << parts.front() << " ";
            parts.pop_front();
        }

        out << parts.front();
        return out.str();
    }
};

const string IntReader::BIGS[] = {"", "Thousand", "Million", "Billion"};
const string IntReader::TENS[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
const string IntReader::SMALLS[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

} // namespace solution2



TEST_CASE("16-08", "[16-08]") {
    REQUIRE(solution1::readNumber(0) == "Zero");
    REQUIRE(solution1::readNumber(7) == "Seven");
    REQUIRE(solution1::readNumber(543) == "Five Hundred Forty Three");
    REQUIRE(solution1::readNumber(11512) == "Eleven Thousand Five Hundred Twelve");
    REQUIRE(solution1::readNumber(2104712638) == "Two Billion One Hundred Four Million Seven Hundred Twelve Thousand Six Hundred Thirty Eight");


    REQUIRE(solution2::IntReader::read(-2104712618) == "Negative Two Billion One Hundred Four Million Seven Hundred Twelve Thousand Six Hundred Eighteen");

}


} // namespace ex_16_08