//
// Created by blazeq on 2017. 10. 11..
//

#include "catch.hpp"
#include <list>
#include <unordered_map>

namespace ex_04_03 {

using namespace std;

struct BstNode {
    int value;
    BstNode* left{nullptr};
    BstNode* right{nullptr};

    BstNode(int v): value(v) {}

    ~BstNode() {
        delete left;
        delete right;
    }
};

bool insert(BstNode*& node, int v) {
    if (node == nullptr) {
        node = new BstNode(v);
        return true;
    }

    bool success;
    if (v < node->value) {
        success = insert(node->left, v);
    } else if (node->value < v) {
        success = insert(node->right, v);
    } else {
        success = false;
    }

    return success;
}

using DepthList = list<int>;
using DepthListMap = unordered_map<int, DepthList>;

void getDepthListsRecurse(BstNode* node, DepthListMap& depthListMap, int depth) {
    if (node == nullptr) {
        return;
    }

    depthListMap[depth].push_back(node->value);
    getDepthListsRecurse(node->left, depthListMap, depth + 1);
    getDepthListsRecurse(node->right, depthListMap, depth + 1);
}

void getDepthLists(BstNode* node, DepthListMap& depthListMap) {
    getDepthListsRecurse(node, depthListMap, 0);
}

TEST_CASE("04-03", "[04-03]") {
    // build BST
    BstNode* tree = nullptr;
    insert(tree, 5);
    insert(tree, 3);
    insert(tree, 1);
    insert(tree, 3);
    insert(tree, 7);
    insert(tree, 6);
    insert(tree, 9);
    insert(tree, 8);

    DepthListMap depthLists;
    getDepthLists(tree, depthLists);

    printf("[04-03] Depth list:\n");
    for (int i = 0; i < depthLists.size(); ++i) {
        printf("depth:%d>", i);
        for (auto id : depthLists[i]) {
            printf(" %d", id);
        }
        printf("\n");
    }

    delete tree;
}

} // namespace ex_04_03