//
// Created by blazeq on 2017. 12. 3..
//

#include <algorithm>
#include <vector>
#include "catch.hpp"

namespace ex_16_15 {

enum Color {R, Y, G, B, NUM_COLORS};
using Colors = std::vector<Color>;

struct HitCount {
    int _hits{0};
    int _pseudoHits{0};

    HitCount(Colors guess, Colors solution) {
        int guessColorCounts[NUM_COLORS] = {0,};
        int solutionColorCounts[NUM_COLORS] = {0,};
        for (int i = 0; i < 4; ++i) {
            guessColorCounts[guess[i]]++;
            solutionColorCounts[solution[i]]++;

            if (guess[i] == solution[i]) {
                _hits++;
            }
        }

        for (int color = 0; color < NUM_COLORS; ++color) {
            _pseudoHits += std::min(guessColorCounts[color], solutionColorCounts[color]);
        }

        _pseudoHits -= _hits;
    }

    int hits() const { return _hits; }
    int pseudoHits() const {return _pseudoHits; }
};

TEST_CASE("16-15", "[16-15]") {
    {
        HitCount r({R, G, B, Y}, {R, Y, G, B});
        REQUIRE(r.hits() == 1);
        REQUIRE(r.pseudoHits() == 3);
    }

    {
        HitCount r({R, G, B, Y}, {G, G, R, R});
        REQUIRE(r.hits() == 1);
        REQUIRE(r.pseudoHits() == 1);
    }
}

} // ex_16_15