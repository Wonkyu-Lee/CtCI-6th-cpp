//
// Created by blazeq on 2017. 11. 12..
//

#include "catch.hpp"

namespace ex_10_08 {

class BitSet {
    int* bits{nullptr};

public:
    BitSet(int size) {
        bits = new int[(size >> 5) + 1];
    }

    ~BitSet() {
        delete [] bits;
    }

    bool get(int pos) {
        int wordNumber = pos >> 5;
        int bitNumber = pos & 0x1f;
        return (bits[wordNumber] & (1 << bitNumber)) != 0;
    }

    void set(int pos) {
        int wordNumber = pos >> 5;
        int bitNumber = pos & 0x1f;
        bits[wordNumber] = bits[wordNumber] | (1 << bitNumber);
    }
};

void checkDuplicates(int arr[], int n) {
    BitSet bitSet(32001);

    for (int i = 0; i < n; ++i) {
        if (bitSet.get(arr[i])) {
            printf("%d, ", arr[i]);
        } else {
            bitSet.set(arr[i]);
        }
    }
}

TEST_CASE("10-08", "[10-08]") {
    int arr[] = {1423, 5213, 3994, 8721, 902, 17, 256, 5213, 17};
    checkDuplicates(arr, sizeof(arr)/sizeof(int));
}

} // namespace ex_10_08
