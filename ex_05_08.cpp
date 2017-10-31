//
// Created by blazeq on 2057. 10. 17..
//

#include <cstdint>
#include <cassert>
#include <iostream>
#include "catch.hpp"

namespace ex_05_08 {

using namespace std;

namespace solutionByQ {

bool drawLine(uint8_t* screen, int w, int h, int x1, int x2, int y) {
    if (w % 8 != 0)
        return false;

    // check input
    if (x2 <= x1) return false;
    if (x1 < 0 || w <= x1) return false;
    if (x2 < 0 || w <= x2) return false;
    if (y < 0 || h <= y) return false;

    int x1Byte = (w * y + x1) / 8; int x1Bit = x1 % 8;
    int x2Byte = (w * y + x2) / 8; int x2Bit = x2 % 8;

    const uint8_t ONES = ~0;

    for (int i = x1Byte; i <= x2Byte; ++i) {
        screen[i] = ONES;
    }

    // if x1Bit = 3, x1ByteMask = 00011111
    uint8_t x1ByteMask = ONES >> x1Bit;

    // if x2Bit = 5, x2ByteMask = 11111000
    uint8_t x2ByteMask = ONES << (8 - x2Bit);

    // if x1Byte = x2Byte, apply x1ByteMask and then x2ByteMask
    screen[x1Byte] = screen[x1Byte] & x1ByteMask;
    screen[x2Byte] = screen[x2Byte] & x2ByteMask;

    return true;
}

bool isBrushed(uint8_t* screen,int w, int x, int y) {
    int byte = (y * w + x) / 8;
    int bit = x % 8;

    // if bit = 2, mask = 00100000 by shifting 00000001 (8 - 3)
    return (screen[byte] & (1 << (8 - (bit + 1)))) != 0;
}

void render(uint8_t* screen, int w, int h) {
    ostringstream canvas;
    for (int j = 0; j < h; ++j) {
        for (int i = 0; i < w; ++i) {
            canvas << (isBrushed(screen, w, i, j) ? '@' : '.');
        }
        canvas << endl;
    }

    cout << canvas.str() << endl;
}

} // solutionByQ


TEST_CASE("05-08", "[05-08]") {
    SECTION("Solution by Q") {
        using namespace solutionByQ;

        SECTION("A valid case (10 ~ 27, 26)")
        {
            enum {W = 64, H = 29};
            uint8_t screen[W/8 * H] = {0,};
            int x1 = 10;
            int x2 = 27;
            int y = 26;
            drawLine(screen, W, H, x1, x2, y);

            render(screen, W, H);

            for (int x = x1; x < x2; ++x) {
                REQUIRE(isBrushed(screen, W, x, y));
            }
        }

        SECTION("A valid case (10 ~ 13, 2)")
        {
            enum {W = 16, H = 16};
            uint8_t screen[W/8 * H] = {0,};
            int x1 = 10;
            int x2 = 13;
            int y = 2;
            drawLine(screen, W, H, x1, x2, y);

            render(screen, W, H);

            for (int x = x1; x < x2; ++x) {
                REQUIRE(isBrushed(screen, W, x, y));
            }
        }

        SECTION("Invalid inputs")
        {
            SECTION("Invalid screen width") {
                enum {W = 63, H = 32};
                uint8_t screen[W/8 * H] = {0,};
                REQUIRE(drawLine(screen, W, H, 5, 43, 12) == false);
            }

            SECTION("X is out of bound") {
                enum {W = 32, H = 16};
                uint8_t screen[W/8 * H] = {0,};
                REQUIRE(drawLine(screen, W, H, 23, 32, 12) == false);
            }

            SECTION("Y is out of bound") {
                enum {W = 32, H = 16};
                uint8_t screen[W/8 * H] = {0,};
                REQUIRE(drawLine(screen, W, H, 23, 25, 32) == false);
            }

            SECTION("X1 is greater than or equals to X2") {
                enum {W = 32, H = 16};
                uint8_t screen[W/8 * H] = {0,};
                REQUIRE(drawLine(screen, W, H, 25, 22, 15) == false);
            }
        }

    }
}

} // namespace ex_05_08