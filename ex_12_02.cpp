//
// Created by blazeq on 2017. 11. 17..
//

#include <iostream>
#include "catch.hpp"

namespace ex_12_02 {
using namespace std;

void reverse(char* str) {
    int len = strlen(str);
    for (int i = 0; i <= len / 2; ++i) {
        swap(str[i], str[len - 1 - i]);
    }
}

TEST_CASE("12-02", "[12-02]") {
    char str[] = "hello";
    reverse(str);
    printf("%s\n", str);
}

} // namespace ex_12_02