//
// Created by blazeq on 2017. 12. 1..
//
#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include "catch.hpp"

namespace ex_16_14 {

using namespace std;

bool equals(float a, float b) {
    static const float epsilon = 0.001f;
    return abs(a - b) <= epsilon;
}

struct Point {
    float x{0};
    float y{0};
    Point() = default;
    Point(float x, float y): x(x), y(y) {}

    bool operator==(const Point& rhs) const {
        return (x == rhs.x) && (y == rhs.y);
    }

    bool operator!=(const Point& rhs) const {
        return !(*this == rhs);
    }
};

// encoding a line uniquely
// TODO: make hash (https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key)
struct Line {
    float a{1};
    float b{1};
    float c{0};

    Line() = default;
    Line(float a, float b, float c): a(a), b(b), c(c) {}

    Line(const Point& p, const Point& q) {
        if (p == q || p.y == q.y) {
            // y = p.y -> y - p.y = 0 -> norm(0, 1, -p.y)
            a = 0;
            b = 1;
            c = -p.y;
            norm(a, b, c);
        } else if (p.x == q.x) {
            // x = p.x -> x - p.x = 0 -> norm(1, 0, -p.x)
            a = 1;
            b = 0;
            c = -p.x;
            norm(a, b, c);
        } else {
            // ax + y + c = 0 ->
            //  a * p.x + p.y + c = 0 and
            //  a * q.x + q.y + c = 0
            //  a = -(p.y - q.y) / (p.x - q.x)
            //  c = -p.y - a * p.x
            a = -(p.y - q.y) / (p.x - q.x);
            b = 1;
            c = -p.y - a * p.x;
            norm(a, b, c);
        }
    }

    bool isPassing(const Point& p) const {
        return isPassing(p.x, p.y);
    }

    bool isPassing(float x, float y) const {
        return equals(a * x + b * y + c, 0);
    }

    bool operator==(const Line& other) const {
        return equals(a, other.a) && equals(b, other.b) && equals(c, other.c);
    }

    bool operator!=(const Line& other) const {
        return !(*this == other);
    }

private:
    static void norm(float& x, float& y, float& z) {
        float d = sqrt(x*x + y*y + z*z);
        if (d == 0)
            return;

        x /= d;
        y /= d;
        z /= d;
    }
};

// TODO: 익히자. hash 만드는 법!!!
struct LineHasher
{
    std::size_t operator()(const Line& k) const
    {
        using std::size_t;
        using std::hash;
        using std::string;

        int a = (int)(k.a * 10000);
        int b = (int)(k.b * 10000);
        int c = (int)(k.c * 10000);

        size_t res = 17;
        res = res * 31 + hash<int>()(a);
        res = res * 31 + hash<int>()(b);
        res = res * 31 + hash<int>()(c);

        return res;
    }
};

Line findMostIntersectingLine(const vector<Point>& points) {
    assert (points.size() > 1);

    unordered_map<Line, unordered_set<size_t>, LineHasher> linePointsMap;
    for (size_t i = 0; i < points.size() - 1; ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            auto& pointSet = linePointsMap[Line(points[i], points[j])];
            pointSet.insert(i);
            pointSet.insert(j);
        }
    }

    Line line;
    int maxCount = -1;
    for (auto& pointSet : linePointsMap) {
        printf("Line: %.2fx + %.2fy +%.2f = 0 with %lu points on.\n",
               pointSet.first.a, pointSet.first.b, pointSet.first.c, pointSet.second.size());
        if (maxCount < pointSet.second.size()) {
            maxCount = pointSet.second.size();
            line = pointSet.first;
        }
    }

    return line;
}

TEST_CASE("16-14", "[16-14]") {
    vector<Point> points = {{0, 1}, {2, 2}, {4, 3}, {-1, 0}, {0, -1}, {4, 0}, {1, 1}, {-2, 0}};
    Line line = findMostIntersectingLine(points);
}

} // namespace ex_16_14