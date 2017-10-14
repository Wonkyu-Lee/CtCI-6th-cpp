//
// Created by blazeq on 2017. 10. 13..
//

#ifndef CTCI_6TH_CPP_BINARYSEARCHTREE_H
#define CTCI_6TH_CPP_BINARYSEARCHTREE_H

#include <functional>
#include <unordered_map>
#include <list>

namespace qds {

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

static BstNode* find(BstNode* node, int v) {
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

static bool insert(BstNode*& node, int v) {
    if (node == nullptr) {
        node = new BstNode(v);
        return true;
    }

    bool success = false;
    if (v < node->value) {
        success = insert(node->left, v);
        node->left->parent = node;
    } else if (node->value < v) {
        success = insert(node->right, v);
        node->right->parent = node;
    } else {
        success = false;
    }

    return success;
}

// returns whether to stop the traversal
static bool inorderTraverse(BstNode* node, std::function<bool(BstNode*, int)> visit, int depth) {
    if (node == nullptr)
        return false;

    if (inorderTraverse(node->left, visit, depth + 1))
        return true;

    if (visit(node, depth))
        return true;

    if (inorderTraverse(node->right, visit, depth + 1))
        return true;

    return false;
}

static BstNode* createFromSortedArray(int* array, int p, int r) {
    if (p > r)
        return nullptr;

    int q = (p + r) / 2;

    BstNode* node = new BstNode(array[q]);

    node->left = createFromSortedArray(array, p, q - 1);
    if (node->left)
        node->left->parent = node;

    node->right = createFromSortedArray(array, q + 1, r);
    if (node->right)
        node->right->parent = node;

    return node;
}

static size_t getNodeCount(BstNode* node) {
    if (node == nullptr)
        return 0;

    return getNodeCount(node->left) + getNodeCount(node->right) + 1;
}

static void depthFirstSearch(BstNode* node, std::function<bool(BstNode*)> visit) {
    if (node == nullptr)
        return;

    std::list<BstNode*> queue;
    queue.push_back(node);

    while (!queue.empty()) {
        BstNode* u = queue.front();
        queue.pop_front();
        if (visit(u))
            break;

        if (u->left != nullptr)
            queue.push_back(u->left);

        if (u->right != nullptr)
            queue.push_back(u->right);
    }
}

using RankMap = std::unordered_map<BstNode*, int>;

static int getRanksRecurse(BstNode* node, RankMap& ranks) {
    if (node == nullptr) {
        return -1;
    }

    int lRank = getRanksRecurse(node->left, ranks);
    int rRank = getRanksRecurse(node->right, ranks);
    int rank = std::max(lRank, rRank) + 1;
    ranks[node] = rank;
    return rank;
}

static RankMap getRanks(BstNode* node) {
    RankMap ranks(getNodeCount(node));
    getRanksRecurse(node, ranks);
    return ranks;
}

using DepthMap = std::unordered_map<int, int>;

static void getDepthsRecurse(BstNode* node, DepthMap& depthMap, int depth) {
    if (node == nullptr) {
        return;
    }

    depthMap[node->value] = depth;
    getDepthsRecurse(node->left, depthMap, depth + 1);
    getDepthsRecurse(node->right, depthMap, depth + 1);
}

static void getDepths(BstNode* node, DepthMap& depthMap) {
    getDepthsRecurse(node, depthMap, 0);
}

} // namespace qds


#endif //CTCI_6TH_CPP_BINARYSEARCHTREE_H
