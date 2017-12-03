//
// Created by blazeq on 2017. 12. 1..
//

#include "catch.hpp"

namespace ex_16_13 {

struct Point {
    float x{0};
    float y{0};
    Point() = default;
    Point(float x, float y): x(x), y(y) {}

    bool operator==(const Point& rhs) const {
        return (x == rhs.x) && (y == rhs.y);
    }
};

struct Square {
    Point center;
    float length{1};
    Square() = default;
    Square(float cX, float cY, float length): center(cX, cY), length(length) {}
};

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
        const float epsilon = 0.001f;
        return abs(a * x + b * y + c) <= epsilon;
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

Line bisectTwoSquares(const Square& sqr1, const Square& sqr2) {
    return Line(sqr1.center, sqr2.center);
}

TEST_CASE("16-13", "[16-13]") {
    {
        Square sqr1(0, 0, 2);
        Square sqr2(3, 3, 4);
        Line line = bisectTwoSquares(sqr1, sqr2);
        REQUIRE(line.isPassing(sqr1.center));
        REQUIRE(line.isPassing(sqr2.center));
    }

    {
        Square sqr1(-62, 11, 15);
        Square sqr2(516, 123, 59);
        Line line = bisectTwoSquares(sqr1, sqr2);
        REQUIRE(line.isPassing(sqr1.center));
        REQUIRE(line.isPassing(sqr2.center));
    }
}

} // namespace ex_16_13