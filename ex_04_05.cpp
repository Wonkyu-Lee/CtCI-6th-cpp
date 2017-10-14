//
// Created by blazeq on 2017. 10. 11..
//

#include "catch.hpp"
#include <list>
#include <unordered_map>

namespace ex_04_05 {

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

BstNode* find(BstNode* node, int v) {
    if (node == nullptr) {
        return nullptr;
    }

    if (v < node->value) {
        return find(node->left, v);
    } else if (node->value < v) {
        return find(node->right, v);
    } else {
        return node;
    }
}

bool isBinarySearchTree(BstNode* node) {
    if (node == nullptr) {
        return true;
    }

    if (!isBinarySearchTree(node->left))
        return false;

    if (!isBinarySearchTree(node->right))
        return false;

    if (node->left) {
        if (!(node->left->value < node->value))
            return false;
    }

    if (node->right) {
        if (!(node->value < node->right->value))
            return false;
    }

    return true;
}

TEST_CASE("04-05", "[04-05]" ) {
    SECTION("Valid BST") {
        BstNode* tree = nullptr;
        insert(tree, 5);
        insert(tree, 3);
        insert(tree, 1);
        insert(tree, 2);
        insert(tree, 4);
        insert(tree, 8);
        insert(tree, 7);
        insert(tree, 6);

        REQUIRE(isBinarySearchTree(tree));

        delete tree;
    }

    SECTION("Invalid BST") {
        BstNode* tree = nullptr;
        insert(tree, 5);
        insert(tree, 3);
        insert(tree, 7);
        insert(tree, 2);

        // make the tree invalid
        BstNode* n3 = find(tree, 3);
        BstNode* n1 = new BstNode(1);
        BstNode* n4 = new BstNode(4);
        n3->right = n1;
        n1->right = n4;

        REQUIRE(isBinarySearchTree(tree) == false);

        delete tree;
    }
}

} // namespace ex_04_05