//
// Created by blazeq on 2017. 10. 11..
//

#include "catch.hpp"
#include <functional>
#include <list>
#include <unordered_map>

namespace ex_04_04 {

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

    bool success = false;
    if (v < node->value) {
        success = insert(node->left, v);
    } else if (node->value < v) {
        success = insert(node->right, v);
    } else {
        success = false;
    }

    return success;
}

bool isBalancedRecurse(BstNode* node, int& rank) {
    if (node == nullptr) {
        rank = -1;
        return true;
    }

    int leftRank;
    if (!isBalancedRecurse(node->left, leftRank)) {
        return false;
    }

    int rightRank;
    if (!isBalancedRecurse(node->right, rightRank)) {
        return false;
    }

    rank = std::max(leftRank, rightRank) + 1;
    return std::abs(leftRank - rightRank) <= 1;
}

bool isBalanced(BstNode* node) {
    int rank;
    return isBalancedRecurse(node, rank);
}

TEST_CASE("04-04", "[04-04]" ) {
    SECTION("Balanced tree") {
        BstNode* tree = nullptr;
        insert(tree, 5);
        insert(tree, 3);
        insert(tree, 7);

        REQUIRE(isBalanced(tree));

        delete tree;
    }

    SECTION("Unbalanced tree") {
        BstNode* tree = nullptr;
        insert(tree, 5);
        insert(tree, 3);
        insert(tree, 7);
        insert(tree, 8);
        insert(tree, 9);

        REQUIRE(isBalanced(tree) == false);

        delete tree;
    }
}

} // namespace ex_04_04