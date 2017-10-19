//
// Created by blazeq on 2017. 11. 11..
//

#include "catch.hpp"

namespace ex_04_08 {

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

TreeNode* findFirstCommonAncestor(TreeNode* n1, TreeNode* n2) {
    TreeNode* p = n1;
    while (p != nullptr) {
        TreeNode* q = n2;
        while (q != nullptr) {
            if (p == q)
                return p;
            q = q->parent;
        }
        p = p->parent;
    }

    return nullptr;
}

TEST_CASE("04-08", "[04-08]") {
    /* Tree
     *     5
     *    / \
     *   2   6
     *  / \   \
     * 1   3   7
     *      \
     *       4
     */

    TreeNode* tree = nullptr;
    TreeNode* n5 = insertToBst(tree, 5);
    TreeNode* n2 = insertToBst(tree, 2);
    TreeNode* n6 = insertToBst(tree, 6);
    TreeNode* n1 = insertToBst(tree, 1);
    TreeNode* n3 = insertToBst(tree, 3);
    TreeNode* n7 = insertToBst(tree, 7);
    TreeNode* n4 = insertToBst(tree, 4);

    REQUIRE(findFirstCommonAncestor(n1, n3) == n2);
    REQUIRE(findFirstCommonAncestor(n1, n7) == n5);
    REQUIRE(findFirstCommonAncestor(n4, n4) == n4);

    delete tree;
}

} // namespace ex_04_08