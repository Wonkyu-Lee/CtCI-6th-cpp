//
// Created by blazeq on 2017. 10. 11..
//

#include "catch.hpp"
#include <unordered_map>

namespace ex_04_02 {

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

BstNode* createFromSortedArray(int* array, int p, int r) {
    if (p > r)
        return nullptr;

    int q = (p + r) / 2;

    BstNode* node = new BstNode(array[q]);
    node->left = createFromSortedArray(array, p, q - 1);
    node->right = createFromSortedArray(array, q + 1, r);

    return node;
}

int getDepth(BstNode* node) {
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
    BstNode* tree = createFromSortedArray(array, 0, 8);

    // print depth of each BST node
    int depth = getDepth(tree);
    printf("[04-02] Tree depth: %d\n", depth);

    delete tree;
}

} // namespace ex_04_02