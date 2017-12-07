//
// Created by blazeq on 2017. 12. 4..
//

#include <iostream>
#include <map>
#include "catch.hpp"

namespace ex_16_22 {

using namespace std;

enum Color { WHITE, BLACK };
enum Direction { UP, DOWN, LEFT, RIGHT };

class Grid {
    using Position = pair<int, int>;

public:
    Grid() = default;

    Color& get(int row, int col) {
        auto p = make_pair(row, col);
        if (_colors.find(p) == _colors.end()) {
            _colors[p] = load(row, col);
            updateBounds(p);
        }

        return _colors[p];
    }

    Color load(int row, int col) {
        return WHITE;
    }

    void updateBounds(const Position& p) {
        if (p.first < _leftTop.first) {
            _leftTop.first = p.first;
        }
        if (p.second < _leftTop.first) {
            _leftTop.second = p.second;
        }
        if (_rightBottom.first < p.first) {
            _rightBottom.first = p.first;
        }
        if (_rightBottom.second < p.second) {
            _rightBottom.second = p.second;
        }
    }

    void print() {
        auto printColor = [](Color c) {
            cout << ((c == BLACK) ? "B" : "W");
        };

        for (int i = _leftTop.first; i <= _rightBottom.first; ++i) {
            for (int j = _leftTop.second; j <= _rightBottom.second; ++j) {
                printColor(get(i, j));
                cout << " ";
            }
            cout << endl;
        }
    }

    void print(int left, int top, int width, int height) {
        auto printColor = [](Color c) {
            cout << ((c == BLACK) ? "B" : "W");
        };

        for (int i = left; i <= left + width - 1; ++i) {
            for (int j = top; j <= top + height - 1; ++j) {
                printColor(get(i, j));
                cout << " ";
            }
            cout << endl;
        }
    }

private:
    map<Position, Color> _colors; // TODO: unordered_map으로 바꿔보자.
    Position _leftTop{0, 0};
    Position _rightBottom{0, 0};
};

void printKMoves(int k) {
    auto rot90CW = [](Direction d) {
        switch (d) {
            case UP: return RIGHT;
            case DOWN: return LEFT;
            case LEFT: return UP;
            case RIGHT: return DOWN;
        }
    };

    auto rot90CCW = [](Direction d) {
        switch (d) {
            case UP: return LEFT;
            case DOWN: return RIGHT;
            case LEFT: return DOWN;
            case RIGHT: return UP;
        }
    };

    Grid grid;

    int r = 0;
    int c = 0;
    Direction d = RIGHT;
    for (int i = 0; i < k; ++i) {
        auto& cell = grid.get(r, c);
        if (cell == WHITE) {
            cell = BLACK;
            d = rot90CW(d);
        } else {
            cell = WHITE;
            d = rot90CCW(d);
        }
        switch (d) {
            case UP: r--; break;
            case DOWN: r++; break;
            case LEFT: c--; break;
            case RIGHT: c++; break;
        }
    }

    grid.print();
}


TEST_CASE("16-22", "[16-22]") {
    printKMoves(16);
}


} // namespace ex_16_22