//
// Created by blazeq on 2017. 11. 11..
//

#include "catch.hpp"

namespace ex_04_08 {

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

BstNode* findFirstCommonAncestor(BstNode* n1, BstNode* n2) {
    BstNode* p = n1;
    while (p != nullptr) {
        BstNode* q = n2;
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

    BstNode* tree = nullptr;
    BstNode* n5 = insert(tree, 5);
    BstNode* n2 = insert(tree, 2);
    BstNode* n6 = insert(tree, 6);
    BstNode* n1 = insert(tree, 1);
    BstNode* n3 = insert(tree, 3);
    BstNode* n7 = insert(tree, 7);
    BstNode* n4 = insert(tree, 4);

    REQUIRE(findFirstCommonAncestor(n1, n3) == n2);
    REQUIRE(findFirstCommonAncestor(n1, n7) == n5);
    REQUIRE(findFirstCommonAncestor(n4, n4) == n4);

    delete tree;
}

} // namespace ex_04_08