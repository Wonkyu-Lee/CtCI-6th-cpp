//
// Created by blazeq on 2017. 12. 3..
//

#include <string>
#include "catch.hpp"

namespace ex_16_18 {

using namespace std;

bool matches(const string& value, const string& pattern, int an, int bn, int al, int bl) {
    string a, b;

    size_t i = 0;
    int aCount = 0;
    int bCount = 0;
    for (auto c : pattern) {
        string w;
        if (c == 'a') {
            if (i + al > value.length())
                return false;

            w = value.substr(i, al);
            if (a.empty()) {
                a = w;
            } else {
                if (a != w)
                    return false;
            }
            ++aCount;
            i += al;
            if (an < aCount)
                return false;
        } else if (c == 'b') {
            if (i + bl > value.length())
                return false;

            w = value.substr(i, bl);
            if (b.empty()) {
                b = w;
            } else {
                if (b != w)
                    return false;
            }
            ++bCount;
            i += bl;
            if (bn < bCount)
                return false;
        }
    }

    return (an == aCount) && (bn == bCount) && (i == value.length());
}

bool matches(const string& value, const string& pattern) {
    int an = 0;
    int bn = 0;
    int vl = value.length();

    if (vl == 0) {
        return true;
    }

    for (auto c : pattern) {
        if (c == 'a') { an++; }
        else if (c == 'b') { bn++; }
    }

    if (an == 0 && bn == 0) {
        return false;
    } else if (an == 0) {
        return matches(value, pattern, 0, bn, 0, vl/bn);
    } else if (bn == 0) {
        return matches(value, pattern, an, 0, vl/an, 0);
    } else {
        // an*al + bn*bl = vl
        // bl = (vl - an*al)/bn
        auto getBl = [&](int al) {
            return (vl - an * al) / bn;
        };

        for (int al = 1; vl - an*al > 0; ++al) {
            int t = vl - an * al;
            if (t % bn != 0)
                continue;
            int bl = getBl(al);
            if (matches(value, pattern, an, bn, al, bl)) {
                return true;
            }
        }

        return false;
    }
}

TEST_CASE("16-18", "[16-18]") {
    REQUIRE(matches("", "aabab"));
    REQUIRE(matches("catcatgocatgo", "aabab"));
    REQUIRE(matches("catcatgocatgo", "aaba") == false);
    REQUIRE(matches("catgogocatcat", "abbaa"));
    REQUIRE(matches("catgogocatcat", "ababaa") == false);
    REQUIRE(matches("hellohellohello", "aaa"));
    REQUIRE(matches("hellohellohello", "aa") == false);
    REQUIRE(matches("googlegoogle", "bb"));
    REQUIRE(matches("googlegoogle", "bbb") == false);
}

} // namespace ex_16_18