//
// Created by blazeq on 2017. 11. 17..
//

#include "catch.hpp"
#include <iostream>
#include <unordered_map>

namespace ex_12_09 {

using namespace std;

template <typename T>
class SharedPtr {
    T* _rp{nullptr};

public:
    SharedPtr(T* rp)
    :_rp(rp) {
        incRefCount();
    }

    ~SharedPtr() {
        decRefCount();
    }

    SharedPtr(const SharedPtr& rhs) {
        _rp = rhs._rp;
        incRefCount();
    }

    SharedPtr& operator=(const SharedPtr& rhs) {
        if (this == &rhs)
            return *this;

        if (_rp == rhs._rp)
            return *this;

        decRefCount();
        _rp = rhs._rp;
        incRefCount();
        return *this;
    }

    T& operator*() {
        return *_rp;
    }

    T* operator->() {
        return _rp;
    }

    int refCount() {
        if (_rp == nullptr)
            return 0;

        return refCounts()[_rp];
    }

private:
    void incRefCount() {
        if (_rp == nullptr)
            return;

        ++refCounts()[_rp];
    }

    void decRefCount() {
        if (_rp == nullptr)
            return;

        int& rc = refCounts()[_rp];
        --rc;

        if (rc == 0) {
            delete _rp;
            refCounts().erase(_rp);
        }
    }

    static unordered_map<T*, int>& refCounts() {
        static unordered_map<T*, int> s_refCounts;
        return s_refCounts;
    };
};

TEST_CASE("12-09", "[12-09]") {
    class Obj {
    public:
        Obj(int id):id(id) {
            cout << "Obj(" << id << ")" << endl;
        }
        ~Obj() {
            cout << "~Obj(" << id << ")" << endl;
        }

        int id{0};
    };

    SharedPtr<Obj> p1 = new Obj(1);
    REQUIRE(p1.refCount() == 1);
    REQUIRE(p1->id == 1);
    REQUIRE((*p1).id == 1);

    {
        SharedPtr<Obj> p2 = p1;
        REQUIRE(p1.refCount() == 2);
        REQUIRE(p2.refCount() == 2);
        REQUIRE(p2->id == 1);
        REQUIRE((*p2).id == 1);
    }

    REQUIRE(p1.refCount() == 1);

    {
        SharedPtr<Obj> p2 = new Obj(2);
    }

    SharedPtr<Obj> p3(new Obj(3));
    p1 = p3;
    REQUIRE(p1->id == 3);
    REQUIRE(p3->id == 3);
}

} // namespace ex_12_09