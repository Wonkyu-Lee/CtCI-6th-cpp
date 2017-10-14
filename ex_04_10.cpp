//
// Created by blazeq on 2017. 10. 11..
//

#include "catch.hpp"

namespace ex_04_10 {

using namespace std;

struct TreeNode {
    int value;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};

    TreeNode(int v): value(v) {}
    ~TreeNode() { delete left; delete right; }
};

TreeNode* createFromSortedArray(int* array, int p, int r) {
    if (p > r)
        return nullptr;

    int q = (p + r) / 2;

    TreeNode* node = new TreeNode(array[q]);
    node->left = createFromSortedArray(array, p, q - 1);
    node->right = createFromSortedArray(array, q + 1, r);

    return node;
}

bool equals(TreeNode* lhs, TreeNode* rhs) {
    if (lhs == nullptr && rhs == nullptr) {
        return true;
    } else if (lhs == nullptr) {
        return false;
    } else if (rhs == nullptr) {
        return false;
    }

    if ((lhs->value != rhs->value))
        return false;

    if (!equals(lhs->left, rhs->left))
        return false;

    if (!equals(lhs->right, rhs->right))
        return false;

    return true;
}

TreeNode* includes(TreeNode* t1, TreeNode* t2) {
    if (t1 == nullptr)
        return nullptr;

    if (equals(t1, t2))
        return t1;

    TreeNode* r = nullptr;

    r = includes(t1->left, t2);
    if (r != nullptr)
        return r;

    r = includes(t1->right, t2);
    if (r != nullptr)
        return r;

    return nullptr;
}

int getRank(TreeNode* node) {
    if (node == nullptr) {
        return -1;
    }
    
    int lRank = getRank(node->left);
    int rRank = getRank(node->right);
    return std::max(lRank, rRank) + 1;
}

int findNodeWithRank(TreeNode* node, vector<TreeNode*>& founds, int targetRank) {
    if (node == nullptr) {
        return -1;
    }

    int lRank = findNodeWithRank(node->left, founds, targetRank);
    int rRank = findNodeWithRank(node->right, founds, targetRank);
    int rank = std::max(lRank, rRank) + 1;

    if (rank == targetRank)
        founds.push_back(node);

    return rank;
}

TreeNode* includesUsingRanks(TreeNode* t1, TreeNode* t2) {
    int t2Rank = getRank(t2);

    vector<TreeNode*> founds;
    findNodeWithRank(t1, founds, t2Rank);

    for (auto each : founds) {
        if (equals(each, t2))
            return each;
    }

    return nullptr;
}

TEST_CASE("04-10", "[04-10]") {

    SECTION("Tree equality") {
        SECTION("Equal trees") {
            int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            TreeNode* lhs = createFromSortedArray(array, 0, 8);
            TreeNode* rhs = createFromSortedArray(array, 0, 8);

            REQUIRE(equals(lhs, rhs));
            REQUIRE(includes(lhs, rhs) == lhs);

            delete lhs;
            delete rhs;
        }

        SECTION("Not equal trees") {
            int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            TreeNode* lhs = createFromSortedArray(array, 0, 6);
            TreeNode* rhs = createFromSortedArray(array, 2, 8);

            REQUIRE(equals(lhs, rhs) == false);

            delete lhs;
            delete rhs;
        }
    }

    SECTION("Inclusion - Brute force") {
        SECTION("Include trees: true case") {
            int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            TreeNode* lhs = createFromSortedArray(array, 0, 8);
            TreeNode* rhs = createFromSortedArray(array, 5, 8);

            TreeNode* r = includes(lhs, rhs);
            REQUIRE(r != nullptr);
            REQUIRE(r->value == 7);

            delete lhs;
            delete rhs;
        }

        SECTION("Include trees: false case") {
            int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            TreeNode* lhs = createFromSortedArray(array, 0, 8);
            TreeNode* rhs = createFromSortedArray(array, 4, 8);

            TreeNode* r = includes(lhs, rhs);
            REQUIRE(r == nullptr);

            delete lhs;
            delete rhs;
        }
    }

    SECTION("Inclusion - using ranks") {
        SECTION("Include trees: true case") {
            int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            TreeNode* lhs = createFromSortedArray(array, 0, 8);
            TreeNode* rhs = createFromSortedArray(array, 5, 8);

            TreeNode* r = includesUsingRanks(lhs, rhs);
            REQUIRE(r != nullptr);
            REQUIRE(r->value == 7);

            delete lhs;
            delete rhs;
        }

        SECTION("Include trees: false case") {
            int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            TreeNode* lhs = createFromSortedArray(array, 0, 8);
            TreeNode* rhs = createFromSortedArray(array, 4, 8);

            TreeNode* r = includesUsingRanks(lhs, rhs);
            REQUIRE(r == nullptr);

            delete lhs;
            delete rhs;
        }
    }
}
} // namespace ex_04_10