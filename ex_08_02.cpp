//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <iostream>
#include <list>
#include <unordered_set>

namespace ex_08_02 {

using namespace std;

class Grid {
    int _R;
    int _C;
    bool* _blocked;

public:
    Grid(const bool* blocked, int R, int C): _R(R), _C(C) {
        _blocked = new bool[R * C];
        for (int i = 0; i < R * C; ++i) {
            _blocked[i] = blocked[i];
        }
    }

    int R() const { return _R; }
    int C() const { return _C; }

    bool isBlocked(int r, int c) const {
        return _blocked[r * _C + c];
    }
};

struct Point {
    int r{0};
    int c{0};

    Point() {}
    Point(int r, int c): r(r), c(c) {}

    friend bool operator==(const Point& a, const Point& b);
    friend bool operator!=(const Point& a, const Point& b);

    struct hash {
        size_t operator()(Point const& p) {
            size_t h1 = std::hash<int>{}(p.r);
            size_t h2 = std::hash<int>{}(p.c);
            return h1 ^ (h2 << 1);
        }
    };
};

bool operator==(const Point& a, const Point& b) {
    return (a.r == b.r) && (a.c == b.c);
}

bool operator!=(const Point& a, const Point& b) {
    return !(a == b);
}

namespace solution1 {

bool findPath(const Grid& grid, int r, int c, list<Point>& path) {
    if (r < 0 || c < 0 || grid.isBlocked(r, c))
        return false;

    bool isAtOrigin = (r == 0 && c == 0);

    if (isAtOrigin ||
        findPath(grid, r - 1, c, path) ||
        findPath(grid, r, c - 1, path)) {
        path.push_back(Point(r, c));
        return true;
    }

    return false;
}

bool findPath(const Grid& grid, list<Point>& path) {
    path.clear();
    return findPath(grid, grid.R() - 1, grid.C() - 1, path);
}

} // solution1

namespace solution2 {

using PointSet = unordered_set<Point, Point::hash>;

bool findPath(const Grid& grid, int r, int c, list<Point>& path, PointSet& failedPoints) {
    if (r < 0 || c < 0 || grid.isBlocked(r, c))
        return false;

    if (failedPoints.find(Point(r, c)) != failedPoints.end()) {
        return false;
    }

    bool isAtOrigin = (r == 0 && c == 0);

    if (isAtOrigin ||
        findPath(grid,r - 1, c, path, failedPoints) ||
        findPath(grid, r, c - 1, path, failedPoints)) {
        path.push_back(Point(r, c));
        return true;
    }

    failedPoints.insert(Point(r, c));
    return false;
}

bool findPath(const Grid& grid, list<Point>& path) {
    path.clear();
    PointSet failedPoints;
    return findPath(grid, grid.R() - 1, grid.C() - 1, path, failedPoints);
}

} // namespace solution2

TEST_CASE("08-02", "[08-02]") {
    int R = 8;
    int C = 8;
    bool blocked[] = {
        0, 0, 0, 0, 0, 1, 1, 1,
        0, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };

    Grid grid(blocked, 8, 8);

    SECTION("Solution1") {
        list<Point> path;
        bool exists = solution1::findPath(grid, path);
        if (exists) {
            printf("Path: ");
            for (auto p : path) {
                printf("(%d, %d)->", p.r, p.c);
            }
            printf("\b\b\n");
        }
    }

    SECTION("Solution2") {
        list<Point> path;
        bool exists = solution2::findPath(grid, path);
        if (exists) {
            printf("Path: ");
            for (auto p : path) {
                printf("(%d, %d)->", p.r, p.c);
            }
            printf("\b\b\n");
        }
    }
}

} // namespace ex_08_02