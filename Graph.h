//
// Created by blazeq on 2017. 10. 13..
//

#ifndef CTCI_6TH_CPP_GRAPH_H
#define CTCI_6TH_CPP_GRAPH_H

#include <list>
#include <unordered_map>
#include <algorithm>

namespace qds {

template<typename Key>
class Graph {
    struct Vertex {
        Key id;
        std::list<Key> adj;
        Vertex(Key id_): id(id_) {}
    };

    std::unordered_map<Key, Vertex*> vertices;
    std::unordered_map<Key, size_t> inCounts;

public:
    ~Graph() {
        for (auto each : vertices) {
            delete each.second;
        }
    }

    Graph() = default;

    Graph(const Graph& rhs) {
        *this = rhs;
    }

    Graph& operator=(const Graph& rhs) {
        for (auto each : vertices) {
            delete each.second;
        }

        vertices.clear();
        inCounts.clear();

        for (auto each : rhs.vertices) {
            addVertex(each.first);
        }

        for (auto each : rhs.vertices) {
            Key u = each.first;
            for (auto v : each.second->adj) {
                addEdge(u, v);
            }
        }

        return *this;
    }

    size_t getVertexCount() {
        return vertices.size();
    }

    size_t getEdgeCount() {
        size_t count = 0;
        for (auto each : vertices) {
            count +=  each.second->adj.size();
        }
        return count;
    }

    bool hasVertex(Key id) {
        return vertices.find(id) != vertices.end();
    }

    bool hasEdge(Key u, Key v) {
        if (!hasVertex(u))
            return false;

        if (!hasVertex(v))
            return false;

        auto& adj = vertices[u]->adj;
        auto found = std::find(adj.begin(), adj.end(), v);
        return found != adj.end();
    }

    bool addVertex(Key id) {
        if (hasVertex(id))
            return false;

        vertices[id] = new Vertex(id);
        return true;
    }

    bool addEdge(Key u, Key v) {
        if (!hasVertex(u))
            addVertex(u);

        if (!hasVertex(v))
            addVertex(v);

        auto& adj = vertices[u]->adj;
        auto found = std::find(adj.begin(), adj.end(), v);
        if (found != adj.end())
            return false;

        adj.push_back(v);
        ++inCounts[v];
        return true;
    }

    bool removeVertex(Key u) {
        auto found = vertices.find(u);
        if (found == vertices.end())
            return false;

        // remove the vertex and decrease out-edge count
        {
            auto& adj = found->second->adj;
            for (auto v : adj) {
                --inCounts[v];
            }
        }
        vertices.erase(found);

        // remove in-edges to the vertex
        for (auto each : vertices) {
            auto& adj = each.second->adj;
            auto found = std::find(adj.begin(), adj.end(), u);
            if (found != adj.end()) {
                adj.erase(found);
                --inCounts[u];
            }
        }

        return true;
    }

    bool removeEdge(Key u, Key v) {
        if (!hasVertex(u))
            return false;

        auto& adj = vertices[u]->adj;
        auto found = std::find(adj.begin(), adj.end(), v);
        if (found != adj.end()) {
            adj.erase(found);
            --inCounts[v];
        }

        return true;
    }

    size_t getInEdgeCount(Key id) {
        if (!hasVertex(id))
            return 0;

        return inCounts[id];
    }

    size_t getOutEdgeCount(Key id) {
        if (!hasVertex(id))
            return 0;

        auto found = vertices.find(id);
        return found->second->adj.size();
    }

    std::list<Key> findVertices(std::function<bool(Key)> predicate) {
        std::list<Key> founds;
        for (auto each : vertices) {
            Key v = each.first;
            if (predicate(v)) {
                founds.push_back(v);
            }
        }

        return founds;
    }

    bool hasCycle() {
        Graph<Key> g = *this;
        while (true) {
            std::list<Key> candidates = g.findVertices([&](Key key) {
                return g.getInEdgeCount(key) == 0;
            });

            if (candidates.empty())
                break;

            char v = candidates.front();
            candidates.pop_front();

            g.removeVertex(v);
        };

        return g.getVertexCount() > 0;
    }

    std::list<Key> topologicalSort() {
        std::list<Key> sorted;
        Graph<Key> g = *this;
        while (true) {
            std::list<Key> candidates = g.findVertices([&](Key key) {
                return g.getInEdgeCount(key) == 0;
            });

            if (candidates.empty())
                break;

            char v = candidates.front();
            candidates.pop_front();

            g.removeVertex(v);
            sorted.push_back(v);
        }

        if (g.getVertexCount() > 0)
            return std::list<Key>();

        return sorted;
    }
};

} // namespace qds

#endif //CTCI_6TH_CPP_GRAPH_H
