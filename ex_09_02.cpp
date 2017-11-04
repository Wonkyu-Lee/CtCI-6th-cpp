//
// Created by blazeq on 2017. 11. 3..
//

#include "catch.hpp"
#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>

namespace ex_09_02 {

using namespace std;

class Service {
    class Person {
    public:
        const char* getName() { return name.c_str(); }

    private:
        int id;
        string name;
        unordered_set<int> friends;
        Person(int id, const string& name): id(id), name(name) {}
        friend class Service;
    };

public:
    ~Service() {
        for (auto person : _people) {
            delete person.second;
        }
    }

    int addPerson(const string& name) {
        static int userCount = 0;
        int id = userCount++;
        _people[id] = new Person(id, name);
        return id;
    }

    Person* find(int id) {
        auto found = _people.find(id);
        if (found == _people.end())
            return nullptr;

        return found->second;
    }

    bool makeFriends(int id1, int id2) {
        Person* person1 = find(id1);
        if (person1 == nullptr)
            return false;

        Person* person2 = find(id2);
        if (person2 == nullptr)
            return false;

        person1->friends.insert(id2);
        person2->friends.insert(id1);
        return true;
    }

    bool findPath(int id1, int id2, list<int>& path) {
        path.clear();

        Person* person1 = find(id1);
        if (person1 == nullptr)
            return false;

        Person* person2 = find(id2);
        if (person2 == nullptr)
            return false;

        Search s1(person1), s2(person2);
        Person* collision = nullptr;
        while (!s1.isFinished() || !s2.isFinished()) {
            collision = searchLevel(s1, s2);
            if (collision != nullptr)
                break;
        }

        if (collision == nullptr)
            return false;

        // make a path
        Person* current = collision;
        while (current != nullptr) {
            path.push_front(current->id);
            current = s1.visitedPrevMap[current];
        }

        current = s2.visitedPrevMap[collision];
        while(current != nullptr) {
            path.push_back(current->id);
            current = s2.visitedPrevMap[current];
        }

        return true;
    }

private:
    struct Search {
        list<Person*> queue;
        unordered_map<Person*, Person*> visitedPrevMap;

        Search(Person* root) {
            visitedPrevMap[root] = nullptr;
            queue.push_back(root);
        }

        bool isFinished() {
            return queue.empty();
        }

        bool hasVisited(Person* person) {
            return visitedPrevMap.find(person) != visitedPrevMap.end();
        }
    };

    Person* searchLevel(Search& s1, Search& s2) {
        Person* collision = searchLevelFromTo(s1, s2);
        if (collision != nullptr) {
            return collision;
        }

        return searchLevelFromTo(s2, s1);
    }

    Person* searchLevelFromTo(Search& from, Search& to) {
        for (size_t i = 0; i < from.queue.size(); ++i) {
            Person* u = from.queue.front();
            from.queue.pop_front();

            if (to.hasVisited(u)) {
                return u;
            }

            for (int each : u->friends) {
                Person* v = find(each);
                if (from.hasVisited(v))
                    continue;

                from.visitedPrevMap[v] = u;
                from.queue.push_back(v);
            }
        }

        return nullptr;
    }

private:
    unordered_map<int, Person*> _people;
};

TEST_CASE("09-02", "[09-02]") {
    Service service;
    int lee = service.addPerson("lee");
    int kim = service.addPerson("kim");
    int jeong = service.addPerson("jeong");
    int doh = service.addPerson("doh");
    int choi = service.addPerson("choi");
    int kwon = service.addPerson("kwon");
    int ahn = service.addPerson("ahn");
    int han = service.addPerson("han");
    int moon = service.addPerson("moon");

    service.makeFriends(doh, kwon);
    service.makeFriends(kwon, lee);
    service.makeFriends(kwon, kim);
    service.makeFriends(ahn, lee);
    service.makeFriends(ahn, choi);
    service.makeFriends(lee, jeong);
    service.makeFriends(choi, kim);
    service.makeFriends(choi, han);

    auto printPath = [&](const list<int>& path) {
        for (auto e : path) {
            printf("%s->", service.find(e)->getName());
        }
        if (!path.empty())
            printf("\b\b");
        printf("\n");
    };

    SECTION("doh~jeong success") {
        list<int> path;
        service.findPath(doh, jeong, path);
        list<int> expected{doh, kwon, lee, jeong};
        REQUIRE(path.size() == expected.size());
        auto i = path.begin();
        auto j = expected.begin();
        for (;i != path.end(); ++i, ++j) {
            REQUIRE(*i == *j);
        }

        printPath(path);
    }

    SECTION("lee~lee success") {
        list<int> path;
        service.findPath(lee, lee, path);
        list<int> expected{lee};
        REQUIRE(path.size() == expected.size());
        auto i = path.begin();
        auto j = expected.begin();
        for (;i != path.end(); ++i, ++j) {
            REQUIRE(*i == *j);
        }

        printPath(path);
    }

    SECTION("doh~moon failed") {
        list<int> path;
        REQUIRE(service.findPath(doh, moon, path) == false);
        REQUIRE(path.empty());
    }
}

} // namespace ex_09_02