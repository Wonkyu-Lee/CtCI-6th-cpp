//
// Created by blazeq on 2017. 10. 11..
//

#include "catch.hpp"
#include <vector>
#include <list>

namespace ex_04_01 {

using namespace std;

class Graph {
    size_t _vertexCount;
    vector<list<int>> _adj;

public:
    Graph(size_t vertexCount)
        : _vertexCount(vertexCount)
        , _adj(vertexCount) {}

    void addEdge(int u, int v) {
        _adj[u].push_back(v);
    }

    void breadthFirstSearch(int s, function<bool(int)> visitThenExit) {
        vector<bool> visited(_vertexCount, false);
        list<int> queue;

        visited[s] = true;
        if (visitThenExit(s))
            return;

        queue.push_back(s);

        while (!queue.empty()) {
            int u = queue.front();
            queue.pop_front();

            for (auto v : _adj[u]) {
                if (visited[v])
                    continue;

                visited[v] = true;
                if (visitThenExit(v))
                    return;

                queue.push_back(v);
            }
        }
    }

    bool hasPath(int s, int t) {
        bool pathExists = false;
        breadthFirstSearch(s, [&](int v) {
            if (v == t) {
                pathExists = true;
                return true; // found! stop searching
            }

            return false; // continue searching
        });

        return pathExists;
    }
};

TEST_CASE( "04-01", "[04-01]" ) {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(0, 5);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 1);
    g.addEdge(3, 2);
    g.addEdge(3, 4);

    REQUIRE(g.hasPath(0, 0)); // self-cycle works
    REQUIRE(g.hasPath(0, 1));
    REQUIRE(g.hasPath(0, 3));
    REQUIRE(g.hasPath(1, 2));
    REQUIRE(g.hasPath(5, 2) == false);
    REQUIRE(g.hasPath(4, 2) == false);
}

} // namespace ex_04_01