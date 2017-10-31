//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <list>
#include <iostream>

namespace ex_08_09 {

using namespace std;

void addParen(list<string>& result, int lRemain, int rRemain, char str[], int index) {
    if (lRemain == 0 && rRemain == 0) {
        result.push_back(string(str));
        return;
    }

    if (0 < lRemain) {
        str[index] = '(';
        addParen(result, lRemain - 1, rRemain, str, index + 1);
    }

    if (lRemain < rRemain) {
        str[index] = ')';
        addParen(result, lRemain, rRemain - 1, str, index + 1);
    }
}

void generateParens(list<string>& result, int count) {
    char str[count * 2 + 1];
    str[count * 2] = '\0';
    result.clear();
    addParen(result, count, count, str, 0);
}

TEST_CASE("08-09", "[08-09]") {
    list<string> result;
    generateParens(result, 5);

    for (auto each : result) {
        cout << each << endl;
    }
}

} // namespace ex_08_09