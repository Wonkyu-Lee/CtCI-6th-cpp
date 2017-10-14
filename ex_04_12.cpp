//
// Created by blazeq on 2017. 12. 12..
//

#include <list>
#include <unordered_map>
#include "catch.hpp"

namespace ex_04_12 {

using namespace std;

struct TreeNode {
    int value;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};

    TreeNode(int v): value(v) {}
    ~TreeNode() { delete left; delete right; }
};

void incrementCountOfSum(unordered_map<int, int>& pathCount, int runningSum, int amount) {
    int count = pathCount[runningSum] + amount;
    pathCount[runningSum] = count;
    if (count == 0) {
        pathCount.erase(runningSum);
    }
}

int countPathsWithSumRecurse(TreeNode* node, int targetSum, int runningSum, unordered_map<int, int>& pathCounts) {
    if (node == nullptr) {
        return 0;
    }

    runningSum += node->value;

    size_t pathCount = 0;
    auto found =  pathCounts.find(runningSum - targetSum);
    if (found != pathCounts.end()) {
        pathCount = found->second;
    }

    if (runningSum == targetSum) {
        ++pathCount;
    }

    incrementCountOfSum(pathCounts, runningSum, 1);
    pathCount += countPathsWithSumRecurse(node->left, targetSum, runningSum, pathCounts);
    pathCount += countPathsWithSumRecurse(node->right, targetSum, runningSum, pathCounts);
    incrementCountOfSum(pathCounts, runningSum, -1);

    return pathCount;
}

int countPathsWithSum(TreeNode* node, int targetSum) {
    unordered_map<int, int> pathCounts;
    return countPathsWithSumRecurse(node, targetSum, 0, pathCounts);
}

TEST_CASE("04-12", "[04-12]") {
    // build tree
    TreeNode* tree = nullptr;
    {
        tree = new TreeNode(10);
        tree->left = new TreeNode(5);
        tree->left->left = new TreeNode(3);
        tree->left->left->left = new TreeNode(3);
        tree->right = new TreeNode(-3);
        tree->right->right = new TreeNode(11);
        tree->left->right = new TreeNode(1);
        tree->left->right->right = new TreeNode(2);
        tree->left->left->right = new TreeNode(-2);
    }

    int count = countPathsWithSum(tree, 8);
    printf("Count of paths with sum %d is %d\n", 8, count);

    delete tree;
}
} // namespace ex_04_12