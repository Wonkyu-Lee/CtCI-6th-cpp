//
// Created by blazeq on 2017. 11. 17..
//

#include "catch.hpp"
#include <unordered_set>
#include <unordered_map>
#include <list>

namespace ex_12_08 {
using namespace std;

struct Node {
    using NodeMap = unordered_map<Node*, Node*>;
    using NodeSet = unordered_set<Node*>;

    int v{0};
    Node* child[2]{nullptr, nullptr};

    static Node* create(int v) {
        return new Node(v);
    }

    static void destroy(Node*& node) {
        NodeSet visited;
        node->dfs(visited);
        for (auto each : visited) {
            delete each;
        }
        node = nullptr;
    }

    Node* clone() {
        NodeMap copied;
        return clone(copied);
    }

    list<Node*> dfsNode() {
        list<Node*> nodes;
        NodeSet visited;
        dfs(visited);
        for (auto each : visited) {
            nodes.push_back(each);
        }
        return nodes;
    }

private:
    Node* clone(NodeMap& copied) {
        auto isAlreadyCopied = [&copied](Node* node) {
            return copied.find(node) != copied.end();
        };

        Node* newNode = new Node(v);
        copied[this] = newNode;

        for (int i = 0; i < 2; ++i) {
            if (child[i] != nullptr) {
                if (isAlreadyCopied(child[i])) {
                    newNode->child[i] = copied[child[i]];
                } else {
                    newNode->child[i] = child[i]->clone(copied);
                }
            }
        }

        return newNode;
    }


    void dfs(NodeSet& visited) {
        auto isVisited = [&visited](Node* node) {
            return visited.find(node) != visited.end();
        };

        visited.insert(this);

        for (int i = 0; i < 2; ++i) {
            if (child[i] != nullptr && !isVisited(child[i])) {
                child[i]->dfs(visited);
            }
        }
    }

    Node(int v): v(v) {}
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
};

TEST_CASE("12-08", "[12-08]") {
    Node* n[5];
    for (int i = 0; i < 5; ++i) {
        n[i] = Node::create(i);
    }

    n[0]->child[0] = n[1];
    n[0]->child[1] = n[2];
    n[1]->child[0] = n[3];
    n[1]->child[1] = n[4];
    n[2]->child[0] = n[0];
    n[3]->child[1] = n[4];
    n[4]->child[0] = n[2];

    Node* copy = n[0]->clone();

    auto nodes1 = n[0]->dfsNode();
    auto nodes2 = copy->dfsNode();

    REQUIRE(nodes1.size() == nodes2.size());
    auto it1 = nodes1.begin();
    auto it2 = nodes2.begin();
    while (it1 != nodes1.end()) {
        REQUIRE((*it1)->v == (*it2)->v);
        ++it1;
        ++it2;
    }

    Node::destroy(n[0]);
    Node::destroy(copy);
}

} // namespace ex_12_08