//
// Created by blazeq on 2017. 11. 11..
//

#include <list>
#include <map>
#include "catch.hpp"

namespace ex_04_11 {

using namespace std;

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
    }

    if (value < node->value) {
        insert(node->left, value);
    } else if (node->value < value) {
        insert(node->right, value);
    }
}

size_t getNodeCount(BstNode* node) {
    if (node == nullptr)
        return 0;

    return getNodeCount(node->left) + getNodeCount(node->right) + 1;
}

BstNode* getRandomNode(BstNode* node) {
    if (node == nullptr)
        return nullptr;

    size_t nodeCount = getNodeCount(node);
    size_t walkCount = std::rand() % nodeCount;

    std::list<BstNode*> queue;
    queue.push_back(node);

    while (!queue.empty()) {
        BstNode* u = queue.front();
        queue.pop_front();
        if (walkCount == 0) {
            return u;
        }

        if (u->left != nullptr) {
            queue.push_back(u->left);
        }

        if (u->right != nullptr) {
            queue.push_back(u->right);
        }
        -- walkCount;
    }

    return nullptr;
}

TEST_CASE("04-11", "[04-11]") {
    /* Tree
     *     5
     *    / \
     *   2   6
     *  / \   \
     * 1   3   7
     *      \
     *       4
     */

    BstNode* tree = nullptr;
    insert(tree, 5);
    insert(tree, 2);
    insert(tree, 6);
    insert(tree, 1);
    insert(tree, 3);
    insert(tree, 7);
    insert(tree, 4);

    int tryCount = 10000;
    map<int, int> counts;
    for (int i = 0; i < tryCount; ++i) {
        BstNode* node = getRandomNode(tree);
        ++counts[node->value];
    }

    printf("[04-11] Random selection:\n");
    for (auto each : counts) {
        printf("[%d] %.2f%%\n", each.first, (each.second / (float)tryCount));
    }

    delete tree;
}
} // namespace ex_04_11