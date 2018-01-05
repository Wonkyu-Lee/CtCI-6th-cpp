//
// Created by blazeq on 2017. 12. 10..
//

#include <iostream>
#include <vector>
#include "catch.hpp"

namespace ex_17_08 {

namespace solution {

using namespace std;

using HightWeight = pair<int, int>;
using Sequence = vector<HightWeight>;


//Sequence longestIncreasingSequence(Sequence& array) {
//    sort(array.begin(), array.end());
//}


void permutation(const string& str, const string& prefix) {
    if (str.empty()) {
        cout << prefix << endl;
        return;
    }

    for (int i = 0; i < str.length(); ++i) {
        string rem = str.substr(0, i) + str.substr(i + 1);
        stringstream newPrefix;
        newPrefix << prefix << str[i];
        permutation(rem, newPrefix.str());
    }
}



} // namespace solution

TEST_CASE("17-08", "[17-08]") {


    using namespace solution;
//    HightWeight hw1(172, 69), hw2( 180, 53);

    //solution::permutation("abcde", "");

    cout << pow(2, 1/3.0) << endl;

}

} // namespace ex_17_08