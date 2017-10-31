//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <stack>

namespace ex_08_06 {

using namespace std;
using Stack = stack<int, deque<int>>;

struct Poll {
public:
    Poll(const string& name, int n = 0) : name(name) {
        for (int i = n; i >= 1; --i) {
            stack.push(i);
        }
    }

    void moveDisksTo(Poll& to, Poll& buffer, int n) {
        if (n == 0)
            return;

        moveDisksTo(buffer, to, n - 1);
        moveTopTo(to);
        buffer.moveDisksTo(to, *this, n - 1);
    }

private:
    void moveTopTo(Poll& to) {
        int top = stack.top();
        stack.pop();
        to.stack.push(top);
        printf("Move disk#%d from %s to from %s.\n", top, name.c_str(), to.name.c_str());
    }

    string name;
    Stack stack;
};

TEST_CASE("08-06", "[08-06]") {
    Poll A("A", 3), B("B"), C("C");
    A.moveDisksTo(C, B, 3);
}

} // namespace ex_08_06