//
// Created by blazeq on 2017. 10. 12..
//

#include "catch.hpp"
#include "Graph.h"

namespace ex_04_07 {

using namespace std;
using namespace qds;

bool hasProjectOrder(Graph<char>& g) {
    auto order = g.topologicalSort();

    printf("[04-07] Project order:\n");
    if (order.empty()) {
        printf("No order exists!");
        return false;
    } else {
        for (auto each : order) {
            printf("%c ", each);
        }
        printf("\n");
        return true;
    }
}

TEST_CASE("04-07", "[04-07") {
    SECTION("Project order exists") {
        Graph<char> g;
        g.addVertex('a');
        g.addVertex('b');
        g.addVertex('c');
        g.addVertex('d');
        g.addVertex('e');
        g.addVertex('f');
        g.addEdge('a', 'd');
        g.addEdge('f', 'b');
        g.addEdge('b', 'd');
        g.addEdge('f', 'a');
        g.addEdge('d', 'c');

        REQUIRE(hasProjectOrder(g));
    }

    SECTION("Project order does not exist") {
        Graph<char> g;
        g.addVertex('a');
        g.addVertex('b');
        g.addVertex('c');
        g.addVertex('d');
        g.addVertex('e');
        g.addVertex('f');
        g.addEdge('a', 'd');
        g.addEdge('f', 'b');
        g.addEdge('b', 'd');
        g.addEdge('f', 'a');
        g.addEdge('d', 'c');
        g.addEdge('c', 'f');

        REQUIRE(hasProjectOrder(g) == false);
    }
}

} // namespace ex_04_07