//
// Created by blazeq on 2017. 11. 11..
//

#include "catch.hpp"

namespace ex_04_06 {

using namespace std;

struct TreeNode {
    int value;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
    TreeNode* parent{nullptr};

    TreeNode(int v): value(v) {}

    ~TreeNode() {
        delete left;
        delete right;
    }
};

TreeNode* insertToBst(TreeNode*& node, int value) {
    if (node == nullptr) {
        node = new TreeNode(value);
        return node;
    }

    TreeNode* r = nullptr;
    if (value < node->value) {
        r = insertToBst(node->left, value);
        node->left->parent = node;
    } else if (node->value < value) {
        r = insertToBst(node->right, value);
        node->right->parent = node;
    }

    return r;
}

TreeNode* findLeftMostChild(TreeNode* node) {
    if (node == nullptr)
        return nullptr;

    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

TreeNode* findInorderSuccessor(TreeNode* node) {
    if (node == nullptr)
        return nullptr;

    if (node->right != nullptr)
        return findLeftMostChild(node->right);

    TreeNode* p = node->parent;
    TreeNode* n = node;
    while (p != nullptr && n != p->left) {
        p = p->parent;
        n = n->parent;
    }

    return p;
}

TEST_CASE("04-06", "[04-06]") {
    /* Tree
     *
     *     7
     *    / \
     *   2   8
     *  / \   \
     * 1   5   9
     *    / \
     *   4   6
     *  /
     * 3
     *
     */

    TreeNode* tree = nullptr;
    TreeNode* n7 = insertToBst(tree, 7);
    TreeNode* n2 = insertToBst(tree, 2);
    TreeNode* n8 = insertToBst(tree, 8);
    TreeNode* n1 = insertToBst(tree, 1);
    TreeNode* n5 = insertToBst(tree, 5);
    TreeNode* n9 = insertToBst(tree, 9);
    TreeNode* n4 = insertToBst(tree, 4);
    TreeNode* n6 = insertToBst(tree, 6);
    TreeNode* n3 = insertToBst(tree, 3);

    REQUIRE(findInorderSuccessor(n1) == n2);
    REQUIRE(findInorderSuccessor(n2) == n3);
    REQUIRE(findInorderSuccessor(n3) == n4);
    REQUIRE(findInorderSuccessor(n4) == n5);
    REQUIRE(findInorderSuccessor(n5) == n6);
    REQUIRE(findInorderSuccessor(n6) == n7);
    REQUIRE(findInorderSuccessor(n7) == n8);
    REQUIRE(findInorderSuccessor(n8) == n9);
    REQUIRE(findInorderSuccessor(n9) == nullptr);

    delete tree;
}

} // namespace ex_04_06