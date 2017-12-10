//
// Created by blazeq on 2017. 12. 10..
//

#include "catch.hpp"
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <iostream>

namespace ex_17_07 {

namespace mine {

using namespace std;

using NamePair = pair<string, string>;
using NamePairs = list<NamePair>;
using Vertices = list<string>;
using Callback = function<void(const Vertices&)>;
using FreqList = unordered_map<string, int>;

class NameGraph {
    using Adjs = unordered_set<string>;
    using Visited = unordered_map<string, bool>;
    unordered_map<string, Adjs> _vertices;
public:
    void addNamePair(const NamePair& namePair) {
        _vertices[namePair.first].insert(namePair.second);
        _vertices[namePair.second].insert(namePair.first);
    }

    void forEachSynonymGroup(Callback cb) {
        Visited visited;
        for (auto& each : _vertices) {
            auto& u = each.first;
            if (!visited[u]) {
                Vertices vertices;
                getConnectedComponent(u, visited, vertices);
                cb(vertices);
            }
        }
    }

private:
    const Adjs& getAdjs(const string& name) const {
        auto found = _vertices.find(name);
        if (found == _vertices.end())
            throw "Invalid input: " + name;
        return found->second;
    }

    void getConnectedComponent(const string& u, Visited& visited, Vertices& vertices) {
        visited[u] = true;
        vertices.push_back(u);
        auto& adjs = getAdjs(u);
        for (auto& v : adjs) {
            if (visited[v])
                continue;

            getConnectedComponent(v, visited, vertices);
        }
    }
};

void getFreqList(const FreqList& original, FreqList& result, const NamePairs& namePairs) {
    NameGraph g;
    for (auto& each : namePairs) {
        g.addNamePair(each);
    }

    g.forEachSynonymGroup([&](const Vertices& synonyms) {
        string first;
        int count = 0;
        for (auto& each : synonyms) {
            if (first.empty()) {
                first = each;
            }
            auto found = original.find(each);
            if (found != original.end()) {
                count += found->second;
            }
        }
        result[first] = count;
    });
}

} // mine

TEST_CASE("17-07", "[17-07]") {
    using namespace mine;
    NamePairs namePairs({
        {"Jon",   "John"},
        {"Jon",   "Johnny"},
        {"Chris", "Kris"},
        {"Chris", "Christopher"}
    });

    FreqList original({
        {"John", 15},
        {"Jon", 12},
        {"Chris", 13},
        {"Kris", 4},
        {"Christopher", 19}
    });

    FreqList result;
    getFreqList(original, result, namePairs);

    for (auto& each : result) {
        printf("%s: %d\n", each.first.c_str(), each.second);
    }
    printf("\n");
}

} // namespace ex_17_07