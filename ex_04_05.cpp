//
// Created by blazeq on 2017. 10. 11..
//

#include "catch.hpp"
#include <list>
#include <unordered_map>

namespace ex_04_05 {

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

TreeNode* insertToBst(TreeNode*& node, int v) {
    if (node == nullptr) {
        node = new TreeNode(v);
        return node;
    }

    if (v <= node->value) {
        return insertToBst(node->left, v);
    } else {
        return insertToBst(node->right, v);
    }
}

namespace solution1 {

// it works for BSTs with unique keys
bool checkBstRecurse(TreeNode* node, int& lastValue) {
    if (node == nullptr)
        return true;

    if (node->left != nullptr) {
        if (!checkBstRecurse(node->left, lastValue)) {
            return false;
        }
    }

    if (lastValue > node->value)
        return false;

    lastValue = node->value;

    if (node->right != nullptr) {
        if (!checkBstRecurse(node->right, lastValue)) {
            return false;
        }
    }

    return true;
}

bool checkBst(TreeNode* node) {
    int lastValue = numeric_limits<int>::min();
    return checkBstRecurse(node, lastValue);
}

} // namespace solution1


namespace solution2 {

bool checkBstRecurse(TreeNode* node, int minValue, int maxValue) {
    if (node == nullptr)
        return true;

    // min < value <= max
    if (node->value <= minValue || maxValue < node->value)
        return false;

    if (!checkBstRecurse(node->left, minValue, node->value))
        return false;

    if (!checkBstRecurse(node->right, node->value, maxValue))
        return false;

    return true;
}

bool checkBst(TreeNode* node) {
    int minValue = numeric_limits<int>::min();
    int maxValue = numeric_limits<int>::max();
    return checkBstRecurse(node, minValue, maxValue);
}

} // namespace solution2


TEST_CASE("04-05", "[04-05]" ) {
    SECTION("Solution1") {
        using namespace solution1;

        SECTION("Valid BST without redundancy") {
            TreeNode* tree = nullptr;
            insertToBst(tree, 5);
            insertToBst(tree, 3);
            insertToBst(tree, 1);
            insertToBst(tree, 2);
            insertToBst(tree, 4);
            insertToBst(tree, 8);
            insertToBst(tree, 7);
            insertToBst(tree, 6);

            REQUIRE(checkBst(tree));

            delete tree;
        }

        SECTION("Invalid BST with redundancy") {
            TreeNode* tree = nullptr;
            TreeNode* n5 = insertToBst(tree, 5);
            TreeNode* n3 = insertToBst(tree, 3);
            TreeNode* n7 = insertToBst(tree, 7);
            TreeNode* n2 = insertToBst(tree, 2);

            // make the tree invalid: right children cannot have same value with the parents
            TreeNode* n3a = new TreeNode(3);
            n3->right = n3a;

            // invalid but cannot detect!
            REQUIRE(checkBst(tree) == true);

            delete tree;
        }

        SECTION("Invalid BST without redundancy") {
            TreeNode* tree = nullptr;
            TreeNode* n5 = insertToBst(tree, 5);
            TreeNode* n3 = insertToBst(tree, 3);
            TreeNode* n7 = insertToBst(tree, 7);
            TreeNode* n2 = insertToBst(tree, 2);

            // make the tree invalid
            TreeNode* n6 = new TreeNode(6);
            n3->right = n6;

            REQUIRE(checkBst(tree) == false);

            delete tree;
        }
    }


    SECTION("Solution2") {
        using namespace solution2;

        SECTION("Valid BST without redundancy") {
            TreeNode* tree = nullptr;
            insertToBst(tree, 5);
            insertToBst(tree, 3);
            insertToBst(tree, 1);
            insertToBst(tree, 2);
            insertToBst(tree, 4);
            insertToBst(tree, 8);
            insertToBst(tree, 7);
            insertToBst(tree, 6);

            REQUIRE(checkBst(tree));

            delete tree;
        }

        SECTION("Valid BST with redundancy") {
            TreeNode* tree = nullptr;
            TreeNode* n5 = insertToBst(tree, 5);
            TreeNode* n3 = insertToBst(tree, 3);
            TreeNode* n7 = insertToBst(tree, 7);
            TreeNode* n2 = insertToBst(tree, 2);

            // make the tree invalid: right children cannot have same value with the parents
            TreeNode* n3a = new TreeNode(3);
            n3->right = n3a;

            REQUIRE(checkBst(tree) == false);

            delete tree;
        }

        SECTION("Invalid BST without redundancy") {
            TreeNode* tree = nullptr;
            TreeNode* n5 = insertToBst(tree, 5);
            TreeNode* n3 = insertToBst(tree, 3);
            TreeNode* n7 = insertToBst(tree, 7);
            TreeNode* n2 = insertToBst(tree, 2);

            // make the tree invalid
            TreeNode* n6 = new TreeNode(6);
            n3->right = n6;

            REQUIRE(checkBst(tree) == false);

            delete tree;
        }
    }
}

} // namespace ex_04_05