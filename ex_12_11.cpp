//
// Created by blazeq on 2017. 11. 20..
//

#include <cstdlib>
#include "catch.hpp"

namespace ex_12_11 {

namespace solution1 {

template<typename T>
T** my2DAlloc(int rows, int cols) {
    T** rowPtrs = (T**)malloc(sizeof(T*) * rows);
    for (int i = 0; i < rows; ++i) {
        rowPtrs[i] = (T*)malloc(sizeof(T) * cols);
    }

    return rowPtrs;
}

template<typename T>
void my2DFree(T** ptr, int rows) {
    for (int i = 0; i < rows; ++i)
        free(ptr[i]);
    free(ptr);
}

} // solution1


namespace solution2 {

template<typename T>
T** my2DAlloc(int rows, int cols) {
    size_t header = sizeof(T*) * rows;
    size_t data = sizeof(T) * cols;
    T** rowPtrs = (T**)malloc(header + data);
    if (rowPtrs == nullptr)
        return nullptr;

    T* buffer = (T*)(rowPtrs + header);
    for (int i = 0; i < rows; ++i) {
        rowPtrs[i] = buffer + i * cols;
    }

    return rowPtrs;
}

} // solution2

TEST_CASE("12-11", "[12-11]") {
    {
        using namespace solution1;
        int rows = 2;
        int cols = 3;
        auto A = my2DAlloc<int>(rows, cols);

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                A[row][col] = (row * cols) + col;
            }
        }

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                printf("%3d", A[row][col]);
            }
            printf("\n");
        }

        my2DFree(A, 2);
    }

    {
        using namespace solution2;
        int rows = 2;
        int cols = 3;
        auto A = my2DAlloc<int>(rows, cols);

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                A[row][col] = (row * cols) + col;
            }
        }

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                printf("%3d", A[row][col]);
            }
            printf("\n");
        }

        free(A);
    }
}

} // namespace ex_12_11