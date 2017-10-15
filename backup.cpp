//
// Created by blazeq on 2017. 10. 12..
//

#include "catch.hpp"
#include <functional>
#include <list>
#include <unordered_map>

namespace backup {

using namespace std;

struct TreeNode {
    int value;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
    TreeNode* parent{nullptr};

    TreeNode(int v): value(v) {}

    ~TreeNode() {
        delete left;
        delete right;
    }

    static TreeNode* find(TreeNode* node, int v) {
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

    static bool insert(TreeNode*& node, int v) {
        if (node == nullptr) {
            node = new TreeNode(v);
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
    static bool inorderTraverse(TreeNode* node, function<bool(TreeNode*, int)> visit, int depth) {
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

    static TreeNode* createFromSortedArray(int* array, int p, int r) {
        if (p > r)
            return nullptr;

        int q = (p + r) / 2;

        TreeNode* node = new TreeNode(array[q]);

        node->left = createFromSortedArray(array, p, q - 1);
        if (node->left)
            node->left->parent = node;

        node->right = createFromSortedArray(array, q + 1, r);
        if (node->right)
            node->right->parent = node;

        return node;
    }

    static size_t getNodeCount(TreeNode* node) {
        if (node == nullptr)
            return 0;

        return getNodeCount(node->left) + getNodeCount(node->right) + 1;
    }

    static void depthFirstSearch(TreeNode* node, function<bool(TreeNode*)> visit) {
        if (node == nullptr)
            return;

        list<TreeNode*> queue;
        queue.push_back(node);

        while (!queue.empty()) {
            TreeNode* u = queue.front();
            queue.pop_front();
            if (visit(u))
                break;

            if (u->left != nullptr)
                queue.push_back(u->left);

            if (u->right != nullptr)
                queue.push_back(u->right);
        }
    }

    using RankMap = unordered_map<TreeNode*, int>;

    static int getRanksRecurse(TreeNode* node, RankMap& ranks) {
        if (node == nullptr) {
            return -1;
        }

        int lRank = getRanksRecurse(node->left, ranks);
        int rRank = getRanksRecurse(node->right, ranks);
        int rank = std::max(lRank, rRank) + 1;
        ranks[node] = rank;
        return rank;
    }

    static RankMap getRanks(TreeNode* node) {
        RankMap ranks(getNodeCount(node));
        getRanksRecurse(node, ranks);
        return ranks;
    }

    using DepthMap = unordered_map<int, int>;

    static void getDepthsRecurse(TreeNode* node, DepthMap& depthMap, int depth) {
        if (node == nullptr) {
            return;
        }

        depthMap[node->value] = depth;
        getDepthsRecurse(node->left, depthMap, depth + 1);
        getDepthsRecurse(node->right, depthMap, depth + 1);
    }

    static void getDepths(TreeNode* node, DepthMap& depthMap) {
        getDepthsRecurse(node, depthMap, 0);
    }
};

TEST_CASE("backup", "[04]" ) {
    TreeNode* tree = nullptr;
    TreeNode::insert(tree, 5);
    TreeNode::insert(tree, 3);
    TreeNode::insert(tree, 7);
    TreeNode::insert(tree, 2);
    TreeNode::insert(tree, 1);
    TreeNode::insert(tree, 4);
    TreeNode::insert(tree, 9);
    TreeNode::insert(tree, 6);
    TreeNode::insert(tree, 8);

    size_t nodeCount = TreeNode::getNodeCount(tree);
    vector<int> d(nodeCount, 0); // depth
    int maxDepth = 0;

// fill depths
    TreeNode::inorderTraverse(tree, [&](TreeNode* node, int depth) {
        d[node->value] = depth;
        if (depth > maxDepth)
            maxDepth = depth;

        return false;
    }, 0);

// link nodes with the same depth
    vector<list<TreeNode*>> groups(maxDepth + 1);
    TreeNode::depthFirstSearch(tree, [&](TreeNode* node) {
        int depth = d[node->value];
        groups[depth].push_back(node);
        return false;
    });

// print out each group
//    int depth = 0;
//    for (auto eachGroup : groups) {
//        printf("[depth: %d]", depth);
//        for (auto eachNode : eachGroup) {
//            printf(" %d", eachNode->value);
//        }
//        printf("\n");
//        ++depth;
//    }

    delete tree;
}

}


namespace backup2 {

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

size_t getNodeCount(TreeNode* node) {
    if (node == nullptr)
        return 0;

    return getNodeCount(node->left) + getNodeCount(node->right) + 1;
}

void insert(TreeNode*& node, int value) {
    if (node == nullptr) {
        node = new TreeNode(value);
    }

    if (value < node->value) {
        insert(node->left, value);
    } else if (node->value < value) {
        insert(node->right, value);
    }
}

TreeNode* createRandomTree(int array[], int n) {
    int* indices = new int[n];
    for (int i = 0; i < n; ++i) {
        indices[i] = i;
    }
    TreeNode* node = createFromSortedArray(indices, 0, n - 1);
    delete [] indices;

    // assign array values while BFS
    list<TreeNode*> queue;
    queue.push_back(node);
    while (!queue.empty()) {
        TreeNode* u = queue.front();
        queue.pop_front();
        u->value = array[u->value];

        if (u->left != nullptr)
            queue.push_back(u->left);

        if (u->right != nullptr)
            queue.push_back(u->right);
    }

    return node;
}

using RankMap = unordered_map<int, list<TreeNode*>>;

void shuffle(int array[], int n) {
    list<int> keys(array, array + n);
    list<int> shuffle;
    for (size_t k = n; k >= 1; --k) {
        size_t toRemove = rand() % k;
        auto it = keys.begin();
        for (int i = 0; i < toRemove; ++i)
            ++it;
        shuffle.push_back(*it);
        keys.erase(it);
    }

    int i = 0;
    for (auto each : shuffle) {
        array[i++] = each;
    }
}

int groupByRank(TreeNode* node, RankMap& depthMap) {
    if (node == nullptr) {
        return -1;
    }

    int lDepth = groupByRank(node->left, depthMap);
    int rDepth = groupByRank(node->right, depthMap);
    int depth = std::max(lDepth, rDepth) + 1;
    depthMap[depth].push_back(node);
    return depth;
}

void printTree(TreeNode* tree) {
    RankMap rankMap;
    int rank = groupByRank(tree, rankMap);
    //int bottomSize = pow(2, rank);

    printf("Tree:\n");
    for (int d = rank; 0 <= d; --d) {
        for (auto each : rankMap[d]) {
            printf("%d ", each->value);
        }
        printf("\n");
    }
}

// fun!!!
void printLongPath(TreeNode* node, list<int>& path) {
    if (node == nullptr) {
        printf("path: ");
        for (auto each : path) {
            printf("%d ", each);
        }
        printf("\n");

        return;
    }

    path.push_back(node->value);
    printLongPath(node->left, path);
    printLongPath(node->right, path);
    path.pop_back();
}
} // backup2