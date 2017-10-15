//
// Created by blazeq on 2017. 10. 11..
//

#include "catch.hpp"
#include <list>
#include <unordered_map>
#include <memory>

namespace ex_04_03 {

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

bool insertToBst(TreeNode*& node, int v) {
    if (node == nullptr) {
        node = new TreeNode(v);
        return true;
    }

    bool success;
    if (v < node->value) {
        success = insertToBst(node->left, v);
    } else if (node->value < v) {
        success = insertToBst(node->right, v);
    } else {
        success = false;
    }

    return success;
}

namespace solution1 {

using LevelList = list<TreeNode*>;
using LevelListVector = vector<LevelList>;

void getLevelListsRecurse(TreeNode* node, LevelListVector& result, int level) {
    if (node == nullptr) {
        return;
    }

    if (result.size() == level) {
        result.push_back(LevelList());
    }

    result[level].push_back(node);
    getLevelListsRecurse(node->left, result, level + 1);
    getLevelListsRecurse(node->right, result, level + 1);
}

void getLevelLists(TreeNode* node, LevelListVector& result) {
    result.clear();
    getLevelListsRecurse(node, result, 0);
}

} // namespace solution1

namespace solution2 {

using LevelList = list<TreeNode*>;
using LevelListPtr = shared_ptr<LevelList>;
using LevelListVector = vector<LevelListPtr>;

void getLevelLists(TreeNode* node, LevelListVector& result) {
    result.clear();

    if (node == nullptr) {
        return;
    }

    LevelListPtr current = make_shared<LevelList>();
    current->push_back(node);

    while (!current->empty()) {
        result.push_back(current);

        LevelListPtr parents = current;
        current = make_shared<LevelList>();

        for (auto parent : *parents) {
            if (parent->left != nullptr)
                current->push_back(parent->left);

            if (parent->right != nullptr)
                current->push_back(parent->right);
        }
    }
}

} // namespace solution2



TEST_CASE("04-03", "[04-03]") {

    TreeNode* tree = nullptr;
    insertToBst(tree, 5);
    insertToBst(tree, 3);
    insertToBst(tree, 1);
    insertToBst(tree, 3);
    insertToBst(tree, 7);
    insertToBst(tree, 6);
    insertToBst(tree, 9);
    insertToBst(tree, 8);

    SECTION("Solution1: using DFS") {
        using namespace solution1;

        LevelListVector result;
        getLevelLists(tree, result);

        printf("[04-03.solution1] Level lists:\n");
        int level = 0;
        for (auto& levelList : result) {
            printf("level:%d>", level);
            for (auto each : result[level]) {
                printf(" %d", each->value);
            }
            printf("\n");
            ++level;
        }
    }

    SECTION("Solution2: using BFS") {
        using namespace solution2;

        LevelListVector result;
        getLevelLists(tree, result);

        printf("[04-03.solution2] Level lists:\n");
        int level = 0;
        for (auto& levelList : result) {
            printf("level:%d>", level);
            for (auto each : *result[level]) {
                printf(" %d", each->value);
            }
            printf("\n");
            ++level;
        }
    }

    delete tree;
}

} // namespace ex_04_03