//
// Created by blazeq on 2017. 10. 11..
//

#include "catch.hpp"

namespace ex_04_02 {

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

TreeNode* createMinimalBst(int* sortedArray, int p, int r) {
    if (p > r)
        return nullptr;

    int q = (p + r) / 2;

    TreeNode* node = new TreeNode(sortedArray[q]);
    node->left = createMinimalBst(sortedArray, p, q - 1);
    node->right = createMinimalBst(sortedArray, q + 1, r);

    return node;
}

TreeNode* createMinimalBst(int* sortedArray, int n) {
    return createMinimalBst(sortedArray, 0, n - 1);
}

int getDepth(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }

    int lRank = getDepth(node->left);
    int rRank = getDepth(node->right);
    return std::max(lRank, rRank) + 1;
}


TEST_CASE("04-02", "[04-02]" ) {
    // build BST
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode* tree = createMinimalBst(array, 9);

    // print depth of each BST node
    int depth = getDepth(tree);
    printf("[04-02] Tree depth: %d\n", depth);

    delete tree;
}

} // namespace ex_04_02