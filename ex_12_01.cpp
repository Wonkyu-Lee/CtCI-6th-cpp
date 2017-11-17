//
// Created by blazeq on 2017. 11. 16..
//
#include <iostream>
#include <fstream>
#include <list>
#include "catch.hpp"

namespace ex_12_01 {

using namespace std;

void printLastKLines(const char* fileName) {
    const int K = 3;
    string line[K];
    int size = 0;

    ifstream in(fileName);
    while (!in.eof()) {
        getline(in, line[size % K]);
        ++size;
    }

    int start = (size <= K) ? 0 : (size % K);
    int count = min(K, size);
    for (int i = 0; i < count; ++i) {
        cout << i << " : " << line[(start + i) % K] << endl;
    }
}

TEST_CASE("12-01", "[12-01]") {
    printLastKLines("ReadMe.txt");
}

} // namespace ex_12_01