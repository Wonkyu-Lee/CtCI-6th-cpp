//
// Created by blazeq on 2017. 11. 12..
//

#include "catch.hpp"
#include <iostream>

namespace ex_10_09 {

using namespace std;

struct Pos {
    int row{0};
    int col{0};
    Pos(int r, int c): row(r), col(c) {}
    bool operator==(const Pos& other) {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Pos& other) {
        return !(*this == other);
    }

    static const Pos& NIL() {
        static Pos nil(-1, -1);
        return nil;
    }
};

ostream& operator<<(ostream& s, const Pos& p) {
    return s << "(" << p.row << ", " << p.col << ")";
}

class Array2D {
    int* elements;
    int rowSize;
    int colSize;

public:
    Array2D(int rows, int cols): rowSize(rows), colSize(cols) {
        elements = new int[rows * cols];
    }

    ~Array2D() {
        delete elements;
    }

    int& operator()(int row, int col) {
        return *(elements + row * colSize + col);
    }

    int getRowSize() {
        return rowSize;
    }

    int getColSize() {
        return colSize;
    }

    Pos find(int x) {
        return find (0, rowSize - 1, 0, colSize - 1, x);
    }
    
    Pos find(int sr, int er, int sc, int ec, int x) {
        if (sr > er || sc > ec)
            return Pos(-1, -1);

        int mr = (sr + er) / 2;
        int mc = (sc + ec) / 2;

        int mid = (*this)(mr, mc);
        if (x == mid) {
            return Pos(mr, mc);
        }

        Pos found = Pos::NIL();
        if (x < mid) {
            found = find(sr, mr - 1, sc, ec, x);
            if (found != Pos::NIL()) {
                return found;
            }
            found = find(mr, er, sc, mc - 1, x);
            if (found != Pos::NIL()) {
                return found;
            }
        } else {
            found = find(sr, er, mc +1, er, x);
            if (found != Pos::NIL()) {
                return found;
            }
            found = find(mr +1, er, sc, mc, x);
            if (found != Pos::NIL()) {
                return found;
            }
        }

        return Pos::NIL();
    }
};

TEST_CASE("10-09", "[10-09]") {
    Array2D arr(4, 3);
    for (int row = 0; row < arr.getRowSize(); ++row) {
        for (int col = 0; col < arr.getColSize(); ++col) {
            arr(row, col) = row * arr.getColSize() + col;
        }
    }

    for (int row = 0; row < arr.getRowSize(); ++row) {
        for (int col = 0; col < arr.getColSize(); ++col) {
            printf("%3d ", arr(row, col));
        }
        printf("\n");
    }

    REQUIRE(arr.find(3) == Pos(1, 0));
    REQUIRE(arr.find(11) == Pos(3, 2));
    REQUIRE(arr.find(12) == Pos::NIL());
}

} // namespace ex_10_09