//
// Created by blazeq on 2017. 11. 11..
//

#include "catch.hpp"

namespace ex_04_06 {

using namespace std;

struct BstNode {
    int value;
    BstNode* left{nullptr};
    BstNode* right{nullptr};
    BstNode* parent{nullptr};

    BstNode(int v): value(v) {}

    ~BstNode() {
        delete left;
        delete right;
    }
};

BstNode* insert(BstNode*& node, int value) {
    if (node == nullptr) {
        node = new BstNode(value);
        return node;
    }

    BstNode* r = nullptr;
    if (value < node->value) {
        r = insert(node->left, value);
        node->left->parent = node;
    } else if (node->value < value) {
        r = insert(node->right, value);
        node->right->parent = node;
    }

    return r;
}

BstNode* findInorderSuccessor(BstNode* node) {
    if (node == nullptr)
        return nullptr;

    if (node->right != nullptr)
        return node->right;

    BstNode* p = node->parent;
    BstNode* n = node;
    while (p != nullptr) {
        if (n == p->left)
            return p;

        p = p->parent;
        n = n->parent;
    }

    return nullptr;
}

TEST_CASE("04-06", "[04-06]") {
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
    BstNode* n5 = insert(tree, 5);
    BstNode* n2 = insert(tree, 2);
    BstNode* n6 = insert(tree, 6);
    BstNode* n1 = insert(tree, 1);
    BstNode* n3 = insert(tree, 3);
    BstNode* n7 = insert(tree, 7);
    BstNode* n4 = insert(tree, 4);

    REQUIRE(findInorderSuccessor(n1) == n2);
    REQUIRE(findInorderSuccessor(n2) == n3);
    REQUIRE(findInorderSuccessor(n3) == n4);
    REQUIRE(findInorderSuccessor(n4) == n5);
    REQUIRE(findInorderSuccessor(n5) == n6);
    REQUIRE(findInorderSuccessor(n6) == n7);
    REQUIRE(findInorderSuccessor(n7) == nullptr);

    delete tree;
}

} // namespace ex_04_06