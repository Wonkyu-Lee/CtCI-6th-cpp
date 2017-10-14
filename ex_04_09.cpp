//
// Created by blazeq on 2017. 10. 11..
//

#include "catch.hpp"
#include "Graph.h"

namespace ex_04_09 {

using namespace std;
using namespace qds;

struct BstNode {
    int value;
    BstNode* left{nullptr};
    BstNode* right{nullptr};

    BstNode(int v): value(v) {}
    ~BstNode() { delete left; delete right; }
};

void insert(BstNode*& node, int value) {
    if (node == nullptr) {
        node = new BstNode(value);
        return;
    }

    if (value < node->value) {
        insert(node->left, value);
    } else if (node->value < value) {
        insert(node->right, value);
    }
}

Graph<int> convert(BstNode* node) {
    Graph<int> g;
    if (node == nullptr)
        return g;

    list<BstNode*> queue;
    g.addVertex(node->value);
    queue.push_back(node);
    while (!queue.empty()) {
        BstNode* u = queue.front();
        queue.pop_front();

        if (u->left != nullptr) {
            g.addEdge(u->value, u->left->value);
            queue.push_back(u->left);
        }

        if (u->right != nullptr) {
            g.addEdge(u->value, u->right->value);
            queue.push_back(u->right);
        }
    }

    return g;
}

list<int> getCandidates(Graph<int> g) {
    return g.findVertices([&g](int v){
        return g.getInEdgeCount(v) == 0;
    });
}

void printRecurse(Graph<int> g, vector<int> seq) {
    if (g.getVertexCount() == 0) {
        for (auto v : seq) {
            printf("%d ", v);
        }
        printf("\n");
    }

    auto candidates = getCandidates(g);
    for (auto v : candidates) {
        // TODO: optimize
        Graph<int> newG = g;
        newG.removeVertex(v);

        vector<int> newSeq = seq;
        newSeq.push_back(v);

        printRecurse(newG, newSeq);
    }
}

void printAllTopologicalSequences(BstNode* node) {
    Graph<int> g = convert(node);
    printRecurse(g, vector<int>());
}

TEST_CASE("04-09", "[04-09]") {
    BstNode* tree = nullptr;
    insert(tree, 5);
    insert(tree, 3);
    insert(tree, 8);
    insert(tree, 1);
    insert(tree, 4);
    insert(tree, 7);
    insert(tree, 8);
    insert(tree, 2);
    insert(tree, 6);

    printf("[04-09] All possible sequences to build the input BST:\n");
    printAllTopologicalSequences(tree);
    printf("\n");

    delete tree;
}

} // namespace ex_04_09