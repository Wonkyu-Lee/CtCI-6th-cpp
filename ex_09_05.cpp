//
// Created by blazeq on 2017. 11. 4..
//

#include "catch.hpp"
#include <iostream>
#include <list>
#include <unordered_map>
#include <cassert>
#include <string>

namespace ex_09_05 {

using namespace std;

struct Summary {
    string url;
    string text;

    Summary() {}
    Summary(const string& url, const string& text): url(url), text(text) {}
};

using Result = list<Summary>;
using ResultPtr = shared_ptr<Result>;

class Cache {
    enum { MAX_SIZE = 3 };
    struct Node;

public:
    ~Cache() {
        while (tail != nullptr)
            removeLastNode();
    }

    ResultPtr getResult(const string& query) {
        auto found = results.find(query);
        if (found == results.end()) {
            return nullptr;
        }

        Node* node = found->second;
        moveNodeToFront(found->second);
        return node->result;
    }

    void insertOrUpdateResult(string query, ResultPtr result) {
        Node* node = nullptr;
        auto found = results.find(query);
        if (found == results.end()) {
            node = new Node(query, result);
            insertNodeToFront(node);
            results[query] = node;
        } else {
            node = found->second;
            moveNodeToFront(node);
        }

        if (MAX_SIZE < results.size()) {
            if (tail != nullptr) {
                printf("[Log] remove the oldest cache item (%s)\n", tail->query.c_str());
                results.erase(tail->query);
                removeLastNode();
            }
        }
    }

private:
    struct Node {
        string query;
        ResultPtr result;
        Node* prev{nullptr};
        Node* next{nullptr};
        Node(const string& query, ResultPtr result): query(query), result(result) {}
    };

    void detachNode(Node* node) {
        if (node == head) {
            if (node == tail) {
                head = tail = nullptr;
            } else {
                head = node->next;
                head->prev = nullptr;
            }
        } else if (node == tail) {
            assert (node != head);
            tail = node->prev;
            tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        node->prev = nullptr;
        node->next = nullptr;
    }

    void insertNodeToFront(Node* node) {
        assert(node->prev == nullptr && node->next == nullptr);

        if (head == nullptr) {
            head = node;
            tail = node;
            return;
        }

        node->next = head;
        head->prev = node;
        head = node;
    }

    void moveNodeToFront(Node* node) {
        detachNode(node);
        insertNodeToFront(node);
    }

    void removeLastNode() {
        if (tail->prev == nullptr) {
            delete tail;
            head = tail = nullptr;
            return;
        }

        Node* toDelete = tail;
        tail->prev->next = nullptr;
        tail = tail->prev;
        delete toDelete;
    }

    Node* head{nullptr};
    Node* tail{nullptr};
    unordered_map<string, Node*> results;
};

class SearchService {
public:
    ResultPtr search(const string& query) {
        auto result = cache.getResult(query);
        if (result == nullptr) {
            result = processSearch(query);
            cache.insertOrUpdateResult(query, result);
            printf("[Log] newly searched (%s)\n", query.c_str());
        } else {
            printf("[Log] get cached (%s)\n", query.c_str());
        }

        return result;
    }

private:
    ResultPtr processSearch(const string& query) {
        ResultPtr r = make_shared<Result>();

        if (query == "Eternal Golden Braid") {
            r->push_back(Summary(
                    "https://en.wikipedia.org/wiki/Gödel,_Escher,_Bach",
                    "Gödel, Escher, Bach: An Eternal Golden Braid, also known as GEB, is a 1979 book by Douglas Hofstadter. The tagline \"a metaphorical fugue on minds and ..."
            ));

            r->push_back(Summary(
                    "https://www.goodreads.com/book/show/24113.G_del_Escher_Bach",
                    "Twenty years after it topped the bestseller charts, Douglas R. Hofstadter's Gödel, Escher, Bach: An Eternal Golden Braid is still something of a marvel. Besides ..."
            ));
        } else if (query == "escher") {
            r->push_back(Summary(
                    "https://ko.wikipedia.org/wiki/마우리츠_코르넬리스_에셔",
                    "Explore the beautiful art of M.C. Escher. Learn about the artist's life and work. Get the latest news about exhibitions, learn about the use of M.c. Escher's work, ..."
            ));
            r->push_back(Summary(
                    "www.mcescher.com/",
                    "마우리츠 코르넬리스 에셔(네덜란드어: Maurits Cornelis Escher, [ˈmʌurɪts kɔrˈneːlɪs ˈɛʃər] 듣기 (도움말·정보), 1898년 6월 17일 ~ 1972년 3월 27일)는 ..."
            ));
        } else if (query == "Gödel") {
            r->push_back(Summary(
                    "https://en.wikipedia.org/wiki/Kurt_Gödel",
                    "Kurt Friedrich Gödel was an Austrian, and later American, logician, mathematician, and philosopher. Considered along with Aristotle, Alfred Tarski and Gottlob ..."
            ));
        } else if (query == "Bach") {
            r->push_back(Summary(
                    "https://www.youtube.com/watch?v=6JQm5aSjX6g",
                    "Subscribe for more classical music: http://bit.ly/YouTubeHalidonMusic Listen to our Bach playlist on Spotify ..."
            ));
        }

        return r;
    }

    Cache cache;
};

TEST_CASE("09-05", "[09-05]") {
    SearchService service;
    list<string> searchSequence{
            "Eternal Golden Braid",
            "escher",
            "escher",
            "Eternal Golden Braid",
            "Gödel",
            "Bach",
            "Bach",
            "escher",
    };

    for (auto& query : searchSequence)
    {
        auto result = service.search(query);
        for (auto& each : *result) {
            printf("url: %s\n%s\n", each.url.c_str(), each.text.c_str());
        }
        printf("\n");
    }
}

} // namespace ex_09_05