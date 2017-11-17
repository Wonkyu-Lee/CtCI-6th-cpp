//
// Created by blazeq on 2017. 11. 12..
//

#include "catch.hpp"

namespace ex_10_10 {

class RankNode {
    RankNode* left{nullptr};
    RankNode* right{nullptr};
    int data{0};
    int leftSize{0};

public:
    RankNode(int d): data(d) {}
    ~RankNode() {
        delete left;
        delete right;
    }

    void insert(int d) {
        if (d <= data) {
            if (left == nullptr) {
                left = new RankNode(d);
            } else {
                left->insert(d);
            }
            ++leftSize;
        } else {
            if (right == nullptr) {
                right = new RankNode(d);
            } else {
                right->insert(d);
            }
        }
    }

    int getRank(int d) {
        if (d == data) {
            return leftSize;
        } else if (d < data) {
            if (left == nullptr) {
                return -1;
            }

            return left->getRank(d);
        } else {
            int rightRank = (right == nullptr) ? -1 : right->getRank(d);
            if (rightRank == -1) {
                return -1;
            }

            return leftSize + 1 + rightRank;
        }
    }
};

class RankManager {
    RankNode* root{nullptr};
public:
    ~RankManager() {
        delete root;
    }

    void track(int number) {
        if (root == nullptr) {
            root = new RankNode(number);
            return;
        }

        root->insert(number);
    }

    int getRankOfNumber(int number) {
        if (root == nullptr) {
            return -1;
        }

        return root->getRank(number);
    }
};

TEST_CASE("10-10", "[10-10]") {
    RankManager rankMgr;
    rankMgr.track(20);
    rankMgr.track(15);
    rankMgr.track(10);
    rankMgr.track(5);
    rankMgr.track(13);
    rankMgr.track(25);
    rankMgr.track(23);
    rankMgr.track(24);

    REQUIRE(rankMgr.getRankOfNumber(5)  == 0);
    REQUIRE(rankMgr.getRankOfNumber(10) == 1);
    REQUIRE(rankMgr.getRankOfNumber(13) == 2);
    REQUIRE(rankMgr.getRankOfNumber(15) == 3);
    REQUIRE(rankMgr.getRankOfNumber(20) == 4);
    REQUIRE(rankMgr.getRankOfNumber(23) == 5);
    REQUIRE(rankMgr.getRankOfNumber(24) == 6);
    REQUIRE(rankMgr.getRankOfNumber(25) == 7);
}

} // namespace ex_10_10