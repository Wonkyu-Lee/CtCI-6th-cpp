//
// Created by blazeq on 2017. 11. 28..
//

#include <map>
#include <iostream>
#include "catch.hpp"

namespace ex_16_02 {
using namespace std;

class BookInfo {
private:
    struct Node {
        map<char, Node*> children;
        int count{0};

        ~Node() {
            for (auto each : children) {
                delete each.second;
            }
        }
    };

    Node* _root{nullptr};

public:
    BookInfo(istream& in) {
        _root = new Node();
        countWords(in);
    }

    ~BookInfo() {
        delete _root;
    }

    int getCountOfWord(const string& word) const {
        return getCountOfWord(_root, word, 0);
    }

private:
    void countWords(istream& in) {
        // TODO: 구둣점 없이  word만 제대로 읽는 법 조사해보자.
        string word;
        while (in >> word) {
            if (!word.empty()) {
                putWord(_root, word, 0);
            }
        }
    }

    void putWord(Node* node, const string& word, size_t index) {
        if (index == word.length()) {
            auto it = node->children.find('\0');
            if (it == node->children.end()) {
                printf("put word first '%s'\n", word.c_str());
                Node* next = new Node();
                next->count = 1;
                node->children['\0'] = next;
            } else {
                Node* next = it->second;
                next->count++;
                printf("put word %dth '%s'\n", next->count, word.c_str());
            }
            return;
        }

        auto it = node->children.find(word[index]);
        Node* next = nullptr;
        if (it == node->children.end()) {
            next = new Node();
            node->children[word[index]] = next;
        } else {
            next = it->second;
        }
        putWord(next, word, index + 1);
    }

    int getCountOfWord(Node* node, const string& word, size_t index) const {
        if (index == word.length()) {
            auto it = node->children.find('\0');
            if (it == node->children.end()) {
                return 0;
            } else {
                Node* next = it->second;
                return next->count;
            }
        }

        auto it = node->children.find(word[index]);
        Node* next = nullptr;
        if (it == node->children.end()) {
            return 0;
        }

        next = it->second;
        return getCountOfWord(next, word, index + 1);
    }
};

TEST_CASE("16-02", "[16-02]") {
    const string bookText =
R"(
a spain hello nice to meet you spain you good to see hello
)";

    istringstream in(bookText);
    BookInfo bookInfo(in);

    REQUIRE(bookInfo.getCountOfWord("spain") == 2);
    REQUIRE(bookInfo.getCountOfWord("you") == 2);
    REQUIRE(bookInfo.getCountOfWord("korea") == 0);
    REQUIRE(bookInfo.getCountOfWord("hello") == 2);
    REQUIRE(bookInfo.getCountOfWord("nice") == 1);
}

} // namespace ex_16_02