//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <iostream>
#include <list>

namespace ex_08_02 {

using namespace std;

struct Point {
    static const Point NIL;

    int r{-1};
    int c{-1};

    Point() {}
    Point(int r, int c): r(r), c(c) {}

    friend bool operator==(const Point& a, const Point& b);
    friend bool operator!=(const Point& a, const Point& b);
};

const Point Point::NIL = Point();

bool operator==(const Point& a, const Point& b) {
    return (a.r == b.r) && (a.c == b.c);
}

bool operator!=(const Point& a, const Point& b) {
    return !(a == b);
}

bool findPath(int* grid, int R, int C, list<Point>& path) {
    auto blocked = [&](int r, int c) -> bool {
        return *(grid + r * C + c) == 1;
    };

    Point prev[R][C]; // initialize with NIL

    for (int r = 1; r < R; ++r) {
        if (blocked(r - 1, 0) == 1)
            prev[r][0] = Point(r - 1, 0);
    }

    for (int c = 1; c < C; ++c) {
        if (blocked(0, c - 1) == 0)
            prev[0][c] = Point(0, c - 1);
    }

    for (int c = 1; c < C; ++c) {
        for (int r = 1; r < R; ++r) {
            bool topBlocked = blocked(r - 1, c);
            bool leftBlocked = blocked(r, c - 1);
            if (!topBlocked) {
                prev[r][c] = Point(r - 1, c);
            } else if (!leftBlocked) {
                prev[r][c] = Point(r, c - 1);
            }
        }
    }

    if (prev[R - 1][C - 1] == Point::NIL)
        return false;

    int r = R - 1;
    int c = C - 1;
    path.push_front(Point(r, c));

    while (prev[r][c] != Point::NIL) {
        path.push_front(prev[r][c]);
        r = prev[r][c].r;
        c = prev[r][c].c;
    }

    return true;
}

TEST_CASE("08-02", "[08-02]") {
    int R = 8;
    int C = 8;
    int grid[] = {
        0, 0, 0, 0, 0, 1, 1, 1,
        0, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };

    list<Point> path;
    bool exists = findPath(grid, R, C, path);
    if (exists) {
        printf("Path: ");
        for (auto p : path) {
            printf("(%d, %d)->", p.r, p.c);
        }
        printf("\b\b\n");
    }
}

} // namespace ex_08_02