//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <list>
#include <iostream>

namespace ex_08_13 {

using namespace std;

struct Vertex {
    list<int> adj;
};

class Graph {
public:
    vector<Vertex> vertices;


    Graph(int vertexCount)
        : vertices(vertexCount) {}

    void addEdge(int u, int v) {
        if (u < 0 || vertices.size() <= u)
            return;

        if (v < 0 || vertices.size() <= v)
            return;

        vertices[u].adj.push_back(v);
    }
};

struct Box {
    int w;
    int h;
    int d;

    Box() {
        int minW = 1;
        int maxW = 5;
        w = (rand() % (maxW - minW)) + minW;
        h = (rand() % (maxW - minW)) + minW;
        d = (rand() % (maxW - minW)) + minW;
    }

    bool biggerThan(Box& other) {
        return (w > other.w) && (h > other.h) && (d > other.d);
    }
};

int getMaxTowerHeight(Box boxes[], int n) {

    Graph g(n);

    // vertex properties
    int inCounts[n];
    int maxHeights[n];
    int prevs[n];

    for (int i = 0; i < n; ++i) {
        inCounts[i] = 0;
        maxHeights[i] = boxes[i].h;
        prevs[i] = -1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (boxes[i].biggerThan(boxes[j])) {
                g.addEdge(i, j);
                ++inCounts[j];
            }
        }
    }

    // find longest path: each value of vertex is its height
    int totalMaxHeight = 0;
    int goal = -1;
    while (true) {
        // find vertex u without in-edges
        int u = -1;
        for (int i = 0; i < n; ++i) {
            if (inCounts[i] == 0) {
                u = i;
                break;
            }
        }
        if (u == -1)
            break;

        // mark used
        inCounts[u] = -1;

        for (auto v : g.vertices[u].adj) {
            --inCounts[v];
        }

        for (auto v : g.vertices[u].adj) {
            int h = maxHeights[u] + boxes[v].h;
            if (maxHeights[v] < h) {
                maxHeights[v] = h;
                prevs[v] = u;
            }

            if (totalMaxHeight < h) {
                totalMaxHeight = h;
                goal = v;
            }
        }
    }

    list<int> path;
    while (goal != -1) {
        path.push_back(goal);
        goal = prevs[goal];
    }

    stringstream ss;
    ss << "Tower: ";
    for (auto u : path) {
        ss << u << "[" << boxes[u].h  << "]->";
    }
    ss << "top";
    cout << ss.str() << endl;

    return totalMaxHeight;
}

TEST_CASE("08-13", "[08-13]") {
    srand(1);
    Box boxes[100];

    printf("Max height of tower: %d\n", getMaxTowerHeight(boxes, sizeof(boxes)/sizeof(Box)));
}

} // namespace ex_08_13