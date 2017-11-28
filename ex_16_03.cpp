//
// Created by blazeq on 2017. 11. 28..
//

#include <cmath>
#include <cassert>
#include "catch.hpp"

namespace ex_16_03 {

bool isZero(float value) {
    const float e = 0.0001f;
    return std::abs(value) <= e;
}

bool equals(float a, float b) {
    return isZero(a - b);
}

class Range {
private:
    float _start{0};
    float _end{1};

public:
    Range() = default;
    Range(float a, float b) {
        if (a <= b) {
            _start = a;
            _end = b;
        } else {
            _start = b;
            _end = a;
        }
    }

    static const Range unit() {
        static const Range range(0, 1);
        return range;
    }

    bool contains(float v) const {
        return (_start <= v && v <= _end);
    }

    bool contains(const Range& other) const {
        return _start <= other._start && other._end <= _end;
    }

    bool hasNoIntersection(const Range& other) const{
        bool lOut = other._end < _start;
        bool rOut = _end < other._start;
        return lOut || rOut;
    }

    bool getInterSection(Range& intersection, const Range& other) const {
        if (hasNoIntersection(other)) {
            return false;
        }

        if (contains(other)) {
            intersection = other;
            return true;
        } else if (other.contains(*this)) {
            intersection = *this;
            return true;
        }

        if (_start < other._start) {
            intersection._start = other._start;
            intersection._end = _end;
        } else {
            intersection._start = _start;
            intersection._end = other._end;
        }
        return true;
    }

    float start() const { return _start; }
    float end() const { return _end; }
};

struct Point {
    float x{0};
    float y{0};

    Point() = default;
    Point(float x, float y): x(x), y(y) {}

    bool equals(const Point& other) {
        return isZero(x - other.x) && isZero(y - other.y);
    }
};

struct Segment {
    Point s;
    Point e;

    Segment() = default;
    Segment(const Point& s, const Point& e): s(s), e(e) {}

    Point at(float t) const {
        Point p;
        p.x = s.x + (e.x - s.x)*t;
        p.y = s.y + (e.y - s.y)*t;
        return p;
    }

    bool containsInLine(const Point& p) const {
        float t = 0;
        return getParameterOfPointOnLine(p, t);
    }

    bool getParameterOfPointOnLine(const Point& p, float& t) const {
        if (isZero(e.x - s.x)) {
            return isZero(p.x - e.x) && Range(s.y, e.y).contains(p.y);
        }

        if (isZero(e.y - s.y)) {
            return isZero(p.y - e.y) && Range(s.x, e.x).contains(p.x);
        }

        float tx = (p.x - s.x) / (e.x - s.x);
        float ty = (p.y - s.y) / (e.y - s.y);

        if (!isZero(tx - ty))
            return false;

        t = tx;
        return true;
    }
};

enum ResultType {
    NONE,
    POINT,
    SEGMENT,
};

struct Result {
    ResultType type{NONE};
    Point point;
    Segment segment;
};

Result getIntersection(const Segment& p, const Segment& q) {
    /* p(u) = p.s + (p.e - p.s)*u
     * q(v) = q.s + (q.e - q.s)*v
     * 
     * p(u) - q(v) = 0
     *
     * (p.e - p.s)*u - (q.e - q.s)*v = q.s - p.s
     *
     * |p.e.x-p.s.x  -q.e.x + q.s.x|   |u|   |q.s.x - p.s.x|
     * |                           | x | | = |             |
     * |p.e.y-p.s.y  -q.e.y + q.s.y|   |v|   |q.s.y - p.s.y|
     *
     * |a b|   |u|   |e|
     * |   | x | | = | |
     * |c d|   |v|   |f|
     *
     *     1      | d -b|   |e|   |u|
     *  ------- x |     | x | | = | |
     *  ad - bc   |-c  a|   |f|   |v|
     *
     */

    Result r;
    float a = p.e.x-p.s.x;
    float b = -q.e.x + q.s.x;
    float c = p.e.y-p.s.y;
    float d = -q.e.y + q.s.y;
    float e = q.s.x - p.s.x;
    float f = q.s.y - p.s.y;

    float D = a * d - b * c;
    if (isZero(D) && p.containsInLine(q.s)) {
        float t1, t2;
        bool success = true;
        success = success && p.getParameterOfPointOnLine(q.s, t1);
        success = success && p.getParameterOfPointOnLine(q.e, t2);
        assert (success);

        Range range(t1, t2);
        Range intersection;
        if (Range(0, 1).getInterSection(intersection, range)) {
            r.type = ResultType::SEGMENT;
            r.segment = Segment(p.at(intersection.start()), p.at(intersection.end()));
            return r;
        }
    } else {
        float u = ((d * e) + (-b * f)) / D;
        float v = ((-c * e) + (a * f)) / D;
        if (Range::unit().contains(u) && Range::unit().contains(v)) {
            r.type = ResultType::POINT;
            r.point = p.at(u);
            return r;
        }
    }

    r.type = ResultType::NONE;
    return r;
}

TEST_CASE("16-03", "[16-03]") {

    SECTION("Test Range") {

        SECTION("Not intersected") {
            Range r1(0, 5);
            Range r2(6, 7);
            Range intersection;
            REQUIRE(r1.getInterSection(intersection, r2) == false);
        }

        SECTION("Contains") {
            Range r1(0, 5);
            Range r2(3, 4);
            REQUIRE(r1.contains(r2));
            REQUIRE(r2.contains(r1) == false);
        }

        SECTION("Intersected") {
            Range r1(0, 5);
            Range r2(3, 7);
            Range intersection;
            REQUIRE(r1.getInterSection(intersection, r2));
            equals(intersection.start(), 3);
            equals(intersection.end(), 5);
        }
    }

    SECTION("Point intersection") {
        Segment segment1(Point(0, 0), Point(2, 2));
        Segment segment2(Point(0, 2), Point(2, 0));
        Result r = getIntersection(segment1, segment2);
        REQUIRE(r.type == ResultType::POINT);
        REQUIRE(r.point.equals(Point(1, 1)));
    }

    SECTION("Not parallel, no intersection") {
        Segment segment1(Point(3, 3), Point(6, 6));
        Segment segment2(Point(0, 2), Point(2, 0));
        Result r = getIntersection(segment1, segment2);
        REQUIRE(r.type == ResultType::NONE);
    }

    SECTION("Overlapping") {
        Segment segment1(Point(0, 0), Point(5, 5));
        Segment segment2(Point(2, 2), Point(4, 4));
        Result r = getIntersection(segment1, segment2);
        REQUIRE(r.type == ResultType::SEGMENT);
    }

    SECTION("In the same line but not overlapping") {
        Segment segment1(Point(0, 0), Point(2, 2));
        Segment segment2(Point(3, 3), Point(4, 4));
        Result r = getIntersection(segment1, segment2);
        REQUIRE(r.type == ResultType::NONE);
    }

    SECTION("Parallel") {
        Segment segment1(Point(0, 0), Point(5, 5));
        Segment segment2(Point(0, 1), Point(5, 6));
        Result r = getIntersection(segment1, segment2);
        REQUIRE(r.type == ResultType::NONE);
    }
}

} // namespace ex_16_03