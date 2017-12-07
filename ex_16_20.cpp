//
// Created by blazeq on 2017. 12. 3..
//

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <sstream>
#include "catch.hpp"

namespace ex_16_20 {

using namespace std;

class Phone {
private:
    class Node {
    public:
        ~Node() {
            for (auto each : _children) {
                delete each.second;
            }
        }

        const Node* getChild(char c) const {
            auto found = _children.find(c);
            if (found == _children.end())
                return nullptr;
            return found->second;
        }

        Node* getChild(char c) {
            auto found = _children.find(c);
            if (found == _children.end())
                return nullptr;
            return found->second;
        }

        Node* createChild(char c) {
            if (getChild(c) != nullptr)
                return nullptr;

            Node* child = new Node();
            _children[c] = child;
            return child;
        }

        void addWord(const string& word) {
            _words.insert(word);
        }

        const set<string>& getWords() const {
            return _words;
        }

    private:
        map<char, Node*> _children;
        set<string> _words;
    };

public:
    Phone() {
        _root = new Node();
    }

    ~Phone() {
        delete _root;
    }

    bool addWord(const string& word) {
        string code = encode(word);
        if (code.empty())
            return false;

        Node* parent = _root;
        Node* node = nullptr;

        for (auto c : code) {
            node = parent->getChild(c);
            if (node == nullptr) {
                node = parent->createChild(c);
            }
            parent = node;
        }

        node->addWord(word);
        return true;
    }

    const set<string>* getCandidates(const string& code) {
        Node* parent = _root;
        Node* node = nullptr;

        for (auto c : code) {
            node = parent->getChild(c);
            if (node == nullptr) {
                return nullptr;
            }
            parent = node;
        }

        return &node->getWords();
    }

private:
    string encode(const string& word) {
        stringstream ss;
        for (auto c : word) {
            auto found = _codes.find(c);
            if (found == _codes.end()) {
                return "";
            }
            ss << found->second;
        }
        return ss.str();
    }

    Node* _root{nullptr};
    const unordered_map<char, char> _codes = {
            {'a', '2'}, {'b', '2'}, {'c', '2'},
            {'d', '3'}, {'e', '3'}, {'f', '3'},
            {'g', '4'}, {'h', '4'}, {'i', '4'},
            {'j', '5'}, {'k', '5'}, {'l', '5'},
            {'m', '6'}, {'n', '6'}, {'o', '6'},
            {'p', '7'}, {'q', '7'}, {'r', '7'}, {'s', '7'},
            {'t', '8'}, {'u', '8'}, {'v', '8'},
            {'w', '9'}, {'x', '9'}, {'y', '9'}, {'z', '9'}
    };
};

TEST_CASE("16-20", "[16-20]") {
    Phone phone;
    phone.addWord("hello");
    phone.addWord("tree");
    phone.addWord("used");

    auto candidates = phone.getCandidates("8733");
    if (candidates != nullptr) {
        for (auto each : *candidates) {
            cout << each << " ";
        }
        cout << endl;
    }
}

} // namespace ex_16_20