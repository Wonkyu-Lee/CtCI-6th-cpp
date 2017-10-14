//
// Created by blazeq on 2017. 10. 13..
//

#include "Graph.h"
#include "catch.hpp"

namespace qds {

using namespace std;

TEST_CASE("Graph fundamentals", "[Graph]" ) {
    Graph<char> g;
    REQUIRE(g.addEdge('a', 'b'));
    REQUIRE(g.addEdge('b', 'c'));
    REQUIRE(g.addEdge('c', 'a'));
    REQUIRE(g.addEdge('d', 'a'));
    REQUIRE(g.getVertexCount() == 4);
    REQUIRE(g.getEdgeCount() == 4);

    SECTION("In-edge count") {
        REQUIRE(g.getInEdgeCount('a') == 2);
        REQUIRE(g.getInEdgeCount('b') == 1);
        REQUIRE(g.getInEdgeCount('c') == 1);
        REQUIRE(g.getInEdgeCount('d') == 0);
    }

    SECTION("Out-edge count") {
        REQUIRE(g.getOutEdgeCount('a') == 1);
        REQUIRE(g.getOutEdgeCount('b') == 1);
        REQUIRE(g.getOutEdgeCount('c') == 1);
        REQUIRE(g.getOutEdgeCount('d') == 1);
    }

    SECTION("Adding an existing vertex fails") {
        REQUIRE(g.addVertex('b') == false);
    }

    SECTION("Adding an existing edge fails") {
        REQUIRE(g.addEdge('b', 'c') == false);
    }

    SECTION("Check vertices exist") {
        REQUIRE(g.hasVertex('a'));
        REQUIRE(g.hasVertex('b'));
        REQUIRE(g.hasVertex('c'));
        REQUIRE(g.hasVertex('d'));
        REQUIRE(g.hasVertex('e') == false);
    }

    SECTION("Check edges exist") {
        REQUIRE(g.hasEdge('a', 'b'));
        REQUIRE(g.hasEdge('b', 'c'));
        REQUIRE(g.hasEdge('c', 'a'));
        REQUIRE(g.hasEdge('a', 'c') == false);
    }

    SECTION("Remove a vertex") {
        REQUIRE(g.removeVertex('a'));
        REQUIRE(g.hasVertex('a') == false);
        REQUIRE(g.hasEdge('a', 'b') == false);
        REQUIRE(g.hasEdge('c', 'a') == false);

        SECTION("In-edge count") {
            REQUIRE(g.getInEdgeCount('a') == 0);
            REQUIRE(g.getInEdgeCount('b') == 0);
            REQUIRE(g.getInEdgeCount('c') == 1);
            REQUIRE(g.getInEdgeCount('d') == 0);
        }

        SECTION("Out-edge count") {
            REQUIRE(g.getOutEdgeCount('a') == 0);
            REQUIRE(g.getOutEdgeCount('b') == 1);
            REQUIRE(g.getOutEdgeCount('c') == 0);
            REQUIRE(g.getOutEdgeCount('d') == 0);
        }

        SECTION("Find vertices without In-edge") {
            auto founds = g.findVertices([&](char v) {
                return g.getInEdgeCount(v) == 0;
            });

            auto contains = [&](char v) {
                return find(founds.begin(), founds.end(), v) != founds.end();
            };

            REQUIRE(contains('b'));
            REQUIRE(contains('d'));
        }
    }

    SECTION("Remove an Edge") {
        REQUIRE(g.removeEdge('a', 'b'));
        REQUIRE(g.hasVertex('a'));
        REQUIRE(g.hasVertex('b'));
        REQUIRE(g.hasEdge('a', 'b') == false);

        SECTION("In-edge count") {
            REQUIRE(g.getInEdgeCount('a') == 2);
            REQUIRE(g.getInEdgeCount('b') == 0);
            REQUIRE(g.getInEdgeCount('c') == 1);
            REQUIRE(g.getInEdgeCount('d') == 0);
        }

        SECTION("Out-edge count") {
            REQUIRE(g.getOutEdgeCount('a') == 0);
            REQUIRE(g.getOutEdgeCount('b') == 1);
            REQUIRE(g.getOutEdgeCount('c') == 1);
            REQUIRE(g.getOutEdgeCount('d') == 1);
        }
    }
}

TEST_CASE("Graph - topological sort", "[Graph]" ) {
    SECTION("Copy constructor") {
        Graph<char> g1;
        g1.addEdge('a', 'b');
        g1.addEdge('a', 'e');
        g1.addEdge('b', 'c');
        g1.addEdge('b', 'd');
        g1.addEdge('d', 'e');

        Graph<char> g2(g1);
        REQUIRE(g1.getVertexCount() == g2.getVertexCount());
        REQUIRE(g1.getEdgeCount() == g2.getEdgeCount());
        REQUIRE(g2.hasVertex('a'));
        REQUIRE(g2.hasVertex('b'));
        REQUIRE(g2.hasVertex('c'));
        REQUIRE(g2.hasVertex('d'));
        REQUIRE(g2.hasVertex('e'));
        REQUIRE(g2.hasEdge('a', 'b'));
        REQUIRE(g2.hasEdge('a', 'e'));
        REQUIRE(g2.hasEdge('b', 'c'));
        REQUIRE(g2.hasEdge('b', 'd'));
        REQUIRE(g2.hasEdge('d', 'e'));
    }

    SECTION("Assignment operator") {
        Graph<char> g1;
        g1.addEdge('a', 'b');
        g1.addEdge('a', 'e');
        g1.addEdge('b', 'c');
        g1.addEdge('b', 'd');
        g1.addEdge('d', 'e');

        Graph<char> g2;
        g2 = g1;
        REQUIRE(g1.getVertexCount() == g2.getVertexCount());
        REQUIRE(g1.getEdgeCount() == g2.getEdgeCount());
        REQUIRE(g2.hasVertex('a'));
        REQUIRE(g2.hasVertex('b'));
        REQUIRE(g2.hasVertex('c'));
        REQUIRE(g2.hasVertex('d'));
        REQUIRE(g2.hasVertex('e'));
        REQUIRE(g2.hasEdge('a', 'b'));
        REQUIRE(g2.hasEdge('a', 'e'));
        REQUIRE(g2.hasEdge('b', 'c'));
        REQUIRE(g2.hasEdge('b', 'd'));
        REQUIRE(g2.hasEdge('d', 'e'));
    }

    SECTION("A graph has no cycle") {
        Graph<char> g;
        g.addEdge('a', 'b');
        g.addEdge('a', 'e');
        g.addEdge('b', 'c');
        g.addEdge('b', 'd');
        g.addEdge('d', 'e');
        REQUIRE(g.hasCycle() == false);
    }

    SECTION("A graph has cycles") {
        Graph<char> g;
        g.addEdge('a', 'b');
        g.addEdge('b', 'c');
        g.addEdge('b', 'd');
        g.addEdge('d', 'e');
        g.addEdge('e', 'a');
        REQUIRE(g.hasCycle());
    }

    SECTION("Topological sort") {
        Graph<char> g;
        g.addEdge('a', 'b');
        g.addEdge('a', 'e');
        g.addEdge('b', 'c');
        g.addEdge('b', 'd');
        g.addEdge('d', 'e');

        printf("Topologically sorted: ");
        auto list = g.topologicalSort();
        for (auto v : list) {
            printf("%c ", v);
        }
        printf("\n");
    }
}

} // namespace qds