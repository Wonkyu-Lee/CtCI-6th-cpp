//
// Created by blazeq on 2017. 12. 4..
//

#include "catch.hpp"
#include <iostream>
#include <unordered_map>

namespace ex_16_25 {

using namespace std;

template<typename Key, typename Value>
class Generator {
public:
    virtual ~Generator() {}
    virtual Value process(const Key& key) = 0;
};

template<typename Key, typename Value>
class Cache {
private:
    struct Node {
        Value value;
        Node* prev{nullptr};
        Node* next{nullptr};
        Node(const Value& value): value(value){}
    };

    size_t _capacity;
    size_t _size;
    Node* _head{nullptr};
    Node* _tail{nullptr};
    unordered_map<Key, Node*> _map;
    Generator<Key, Value>* _generator{nullptr};

public:
    Cache(Generator<Key, Value>* generator, size_t capacity)
            : _generator(generator)
            , _capacity(capacity)
    {}

    const Value& get(const Key& key) {
        auto found = _map.find(key);
        Node* node = nullptr;
        if (found != _map.end()) {
            node = found->second;
            moveToFirst(node);
        } else {
            if (_size == _capacity) {
                removeLast();
            }

            node = addFirst(key);
            _map[key] = node;
        }

        return node->value;
    }

    void debugPrint() {
        Node* node = _head;
        cout << "cache: ";
        while (node != nullptr) {
            cout << node->value << " ";
            node = node->next;
        }
        cout << endl;
    }

private:
    void moveToFirst(Node* node) {
        Node* detached = detachNode(node);
        attachFirst(detached);
    }

    void removeLast() {
        Node* detached = detachNode(_tail);
        delete detached;
        cout << "delete " << detached->value << endl;
        _size--;
    }

    Node* detachNode(Node* node) {
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        }

        if (node->prev != nullptr) {
            node->prev->next = node->next;
        }

        if (node == _head) {
            _head = node->next;
        }

        if (node == _tail) {
            _tail = node->prev;
        }

        node->prev = nullptr;
        node->next = nullptr;
        return node;
    }

    Node* addFirst(const Key& key) {
        Node* node = createNode(key);
        attachFirst(node);
        return node;
    }

    void attachFirst(Node* node) {
        if (_head == nullptr) {
            _head = _tail = node;
        } else {
            node->next = _head;
            _head->prev = node;
            _head = node;
        }
    }

    Node* createNode(const Key& key) {
        _size++;
        return new Node(_generator->process(key));
    }
};

TEST_CASE("16-25", "[16-25]") {
    class EchoGenerator : public Generator<string, string> {
    public:
        string process(const string& key) override
        {
            return key;
        }
    };

    EchoGenerator generator;
    Cache<string, string> cache(&generator, 5);

    cout << cache.get("a") << endl;
    cache.debugPrint();

    cout << cache.get("b") << endl;
    cache.debugPrint();

    cout << cache.get("c") << endl;
    cache.debugPrint();

    cout << cache.get("d") << endl;
    cache.debugPrint();

    cout << cache.get("a") << endl;
    cache.debugPrint();

    cout << cache.get("e") << endl;
    cache.debugPrint();

    cout << cache.get("f") << endl;
    cache.debugPrint();
}

} // namespace ex_16_25