//
// Created by blazeq on 2017. 10. 11..
//

#include "catch.hpp"
#include <functional>
#include <list>
#include <unordered_map>

namespace ex_04_04 {

using namespace std;

struct TreeNode {
    int value;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};

    TreeNode(int v): value(v) {}

    ~TreeNode() {
        delete left;
        delete right;
    }
};

bool insertToBst(TreeNode*& node, int v) {
    if (node == nullptr) {
        node = new TreeNode(v);
        return true;
    }

    bool success = false;
    if (v < node->value) {
        success = insertToBst(node->left, v);
    } else if (node->value < v) {
        success = insertToBst(node->right, v);
    } else {
        success = false;
    }

    return success;
}

bool isBalancedRecurse(TreeNode* node, int& height) {
    if (node == nullptr) {
        height = -1;
        return true;
    }

    int leftHeight;
    if (!isBalancedRecurse(node->left, leftHeight)) {
        return false;
    }

    int rightHeight;
    if (!isBalancedRecurse(node->right, rightHeight)) {
        return false;
    }

    height = std::max(leftHeight, rightHeight) + 1;
    return std::abs(leftHeight - rightHeight) <= 1;
}

bool isBalanced(TreeNode* node) {
    int height;
    return isBalancedRecurse(node, height);
}

TEST_CASE("04-04", "[04-04]" ) {
    SECTION("Balanced tree") {
        TreeNode* tree = nullptr;
        insertToBst(tree, 5);
        insertToBst(tree, 3);
        insertToBst(tree, 7);

        REQUIRE(isBalanced(tree));

        delete tree;
    }

    SECTION("Unbalanced tree") {
        TreeNode* tree = nullptr;
        insertToBst(tree, 5);
        insertToBst(tree, 3);
        insertToBst(tree, 7);
        insertToBst(tree, 8);
        insertToBst(tree, 9);

        REQUIRE(isBalanced(tree) == false);

        delete tree;
    }
}

} // namespace ex_04_04