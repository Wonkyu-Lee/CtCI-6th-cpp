//
// Created by blazeq on 2017. 11. 17..
//

#include <cstdio>
#include "catch.hpp"

namespace ex_12_06 {

void func() {
    const int i = 0;
    int j = 1;
    int k = 2;

    // pointers
    {
        const int* p = &i;
        int const* p2 = &i; // same
        // *p = 5; // compile error!
        p = &j;

        int* const q = &j;
        // int* const q2 = &i; // compile error!
        *q = 5;
        // q = &k; // compile error!

        const int* const r = &j;
        int const* const r2 = &j;
        // *r = 5; // compile error!
        // r = &k; // compile error!
        // *r2 = 5; // compile error!
        // r2 = &k; // compile error!
    }

    // references
    {
        const int& p = i;
        int const& p2 = i;
        // p = 5;
        // p2 = 5;
    }
}

void func2() {
    volatile int i = 0;
    int volatile j = 0;
    int k;

    // pointer to volatile int, not volatile pointer
    volatile int* p = &i;
    p = &j;
    p = &k;

    //int* volatile q = &i; // volatile pointer cannot point volatile variable
    int* volatile q = &k;
    // q = &i;

    volatile int* volatile r = &i;
}

TEST_CASE("12-06", "[12-06]") {
    func();
    func2();
}

} // namespace ex_12_06