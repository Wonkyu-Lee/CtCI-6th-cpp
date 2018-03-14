//
// Created by blazeq on 2018. 1. 11..
//

#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <iomanip>
#include "catch.hpp"

namespace ex_08_12 {

using namespace std;

class QueenPlacing {
    const int N{1};
    using VectorPtr = shared_ptr<vector<int>>;
    list<VectorPtr> results;
    int resultCount{0};

public:
    QueenPlacing(int n): N(n) {
        VectorPtr cols = make_shared<vector<int>>(N);
        resultCount = placeQueen(0, cols);
    }

    friend ostream& operator<<(ostream& o, const QueenPlacing& queenPlacing) {
        o << "count = " << queenPlacing.resultCount << endl;
        for (auto cols : queenPlacing.results) {
            for (auto col : (*cols)) {
                for (int i = 0; i < col; ++i) o << "-";
                o << "@";
                for (int i = 0; i < queenPlacing.N - col - 1; ++i) o << "-";
                o << endl;
            }
            o << "========" << endl;
        }
        return o;
    }

private:
    int placeQueen(int row, VectorPtr cols) {
        if (row == N) {
            VectorPtr clone = make_shared<vector<int>>(0);
            *clone = *cols;
            results.push_back(clone);
            return 1;
        }

        int count = 0;
        for (int col = 0; col < N; ++col) {
            if (isValid(cols, row, col)) {
                (*cols)[row] = col;
                count += placeQueen(row + 1, cols);
            }
        }

        return count;
    }

    bool isValid(VectorPtr cols, int row, int col) {
        for (int i = 0; i < row; ++i) {
            if ((*cols)[i] == col)
                return false;

            if (abs(col - (*cols)[i]) == row - i)
                return false;
        }

        return true;
    }
};

TEST_CASE("08-12", "[08-12]") {
    QueenPlacing queenPlacing(5);
    cout << queenPlacing << endl;
}

} // namespace ex_08_12