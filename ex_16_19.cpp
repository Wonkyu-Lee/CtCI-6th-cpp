//
// Created by blazeq on 2017. 12. 3..
//

#include <list>
#include <stack>
#include <iostream>
#include "catch.hpp"

namespace ex_16_19 {

using namespace std;

struct Position {
    int r{0};
    int c{0};
    Position() = default;
    Position(int r, int c): r(r), c(c) {}
};

template<typename T, size_t M, size_t N>
class Matrix {
    T _array[M][N];

public:
    Matrix(const T& value) {
        for (size_t i = 0; i < M; ++i)
            for (size_t j = 0 ;j < N; ++j)
                _array[i][j] = value;
    }

    Matrix(const T arr[M][N]) {
        for (size_t i = 0; i < M; ++i)
            for (size_t j = 0 ;j < N; ++j)
                _array[i][j] = arr[i][j];
    }

    T& operator()(size_t row, size_t col) {
        return _array[row][col];
    }

    const T& operator()(size_t row, size_t col) const {
        return _array[row][col];
    }

    T& operator()(const Position& p) {
        return _array[p.r][p.c];
    }

    const T& operator()(const Position& p) const {
        return _array[p.r][p.c];
    }

    size_t rowSize() const { return M; }
    size_t colSize() const { return N; }

    bool valid(int r, int c) const {
        return (0 <= r && r < M) && (0 <= c && c < N);
    }

    bool valid(const Position& p) const {
        return valid(p.r, p.c);
    }
};

template<size_t M, size_t N>
size_t calcPondSize(const Matrix<int, M, N>& m, int row, int col, Matrix<bool, M, N>& visited) {
    size_t size = 0;
    stack<Position> st;

    visited(row, col) = true;
    st.push({row, col});
    ++size;

    while (!st.empty()) {
        auto p = st.top(); st.pop();
        Position neighbors[] = {
            {p.r - 1, p.c - 1}, {p.r - 1, p.c}, {p.r - 1, p.c + 1},
            {p.r, p.c - 1}, {p.r, p.c + 1},
            {p.r + 1, p.c - 1}, {p.r + 1, p.c}, {p.r + 1, p.c + 1}
        };

        for (auto& each : neighbors) {
            if (m.valid(each) && !visited(each) && m(each) == 0) {
                st.push(each);
                ++size;
                visited(each) = true;
            }
        }
    }

    return size;
};

template<size_t M, size_t N>
vector<size_t> getPondSizes(const Matrix<int, M, N>& m) {
    vector<size_t> sizes;
    Matrix<bool, M, N> visited(false);

    for (size_t r = 0; r < M; ++r) {
        for (size_t c = 0; c < N; ++c) {
            if (m(r, c) != 0) continue;
            if (visited(r, c)) continue;

            sizes.push_back(calcPondSize(m, r, c, visited));
        }
    }

    return sizes;
}

TEST_CASE("16-19", "[16-19]") {
    int arr[4][4] = {
            {0, 2, 1, 0},
            {0, 1, 0, 1},
            {1, 1, 0, 1},
            {0, 1, 0, 1}
    };

    cout << "sizes: ";
    auto sizes = getPondSizes(Matrix<int, 4, 4>(arr));
    for (auto each : sizes) {
        cout << each << " ";
    }
    cout << endl;
}

} // namespace ex_16_19