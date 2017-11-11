//
// Created by blazeq on 2017. 11. 9..
//

#include "catch.hpp"
#include <iostream>

namespace ex_10_07 {

using namespace std;

class BitSet {
    uint32_t _base{0};
    uint8_t* _bytes{nullptr};
    size_t _bitCount{0};

public:
    class UnsetEnumerator {
        friend class BitSet;
        BitSet& _bitSet;
        uint32_t _current{0};
        UnsetEnumerator(BitSet& bitSet): _bitSet(bitSet), _current(bitSet.getBase()) {}

    public:
        bool next(uint32_t& result) {
            while (_current - _bitSet.getBase() < _bitSet.size()) {
                if (!_bitSet.isSet(_current)) {
                    result = _current;
                    ++_current;
                    return true;
                }

                ++_current;
            }

            return false;
        }
    };

    BitSet(size_t bitCount, uint32_t base = 0): _bitCount(bitCount), _base(base) {
        size_t byteCount = (bitCount / 8) + (bitCount % 8 == 0 ? 0 : 1);
        _bytes = new uint8_t[byteCount];
        memset(_bytes, 0, byteCount);
    }

    BitSet() = default;

    ~BitSet() {
        delete [] _bytes;
    }

    size_t size() {
        return _bitCount;
    }

    uint32_t getBase() {
        return _base;
    }

    void set(uint32_t i) {
        if (_bitCount <= i - _base)
            return;

        uint32_t byte = (i - _base) / 8;
        uint32_t bit = (i - _base) % 8;
        _bytes[byte] = _bytes[byte] | (1 << (8 - 1 - bit));
    }

    void reset(uint32_t i) {
        if (_bitCount <= i - _base)
            return;

        uint32_t byte = (i - _base) / 8;
        uint32_t bit = (i - _base) % 8;
        _bytes[byte] = _bytes[byte] & ~(1 << (8 - 1 - bit));
    }

    bool isSet(uint32_t i) {
        if (_bitCount <= i - _base)
            return false;

        uint32_t byte = (i - _base) / 8;
        uint32_t bit = (i - _base) % 8;
        return _bytes[byte] & (1 << (8 - 1 - bit));
    }

    UnsetEnumerator getUnsetEnumerator() {
        return UnsetEnumerator(*this);
    }

    bool store(const char* fileName) {
        FILE* fp = fopen(fileName, "wb");
        if (fp == nullptr)
            return false;

        fwrite(&_base, sizeof(_base), 1, fp);
        fwrite(&_bitCount, sizeof(_bitCount), 1, fp);
        size_t byteCount = (_bitCount / 8) + (_bitCount % 8 == 0 ? 0 : 1);
        fwrite(_bytes, sizeof(uint8_t), byteCount, fp);
        fclose(fp);
        return true;
    }

    // TODO: 예외처리
    bool load(const char* fileName) {
        FILE* fp = fopen(fileName, "rb");
        if (fp == nullptr)
            return false;

        fread(&_base, sizeof(_base), 1, fp);
        fread(&_bitCount, sizeof(_bitCount), 1, fp);
        size_t byteCount = (_bitCount / 8) + (_bitCount % 8 == 0 ? 0 : 1);
        _bytes = new uint8_t(byteCount);
        fread(_bytes, 1, byteCount, fp);
        fclose(fp);

        return true;
    }
};

TEST_CASE("10-07", "[10-07]") {
    auto isPrime = [](int n) {
        if (n < 2)
            return false;

        for (int i = 2; i <= sqrt(n); ++i) {
            if (n % i == 0)
                return false;
        }
        return true;
    };

    SECTION("Store/Load") {
        const char* fileName = "bitSet.dat";

        // store
        {
            BitSet bitSet(100);
            for (int i = 0; i < 100; ++i) {
                if (!isPrime(i)) {
                    bitSet.set(i);
                }
            }
            bitSet.store(fileName);
        }

        // load
        {
            BitSet bitSet;
            bitSet.load(fileName);
            auto enumerator = bitSet.getUnsetEnumerator();
            uint32_t r;
            while (enumerator.next(r)) {
                printf("%d, ", r);
            }
            printf("\n");
        }
    }

    SECTION("N = 4000000000, 1GB") {
        const char* fileName = "integers.dat";
        enum {
            NUM_INTS = 100,     // count of integers stored in the given file
            MAX_INT = 200,      // max integer value
        };

        // make file
        {
            uint32_t k = 0;

            printf("integers: ");
            FILE* fp = fopen(fileName, "wb");
            for (uint32_t i = 0; i < NUM_INTS; ++i) {
                while (isPrime(k)) {
                    ++k;
                    continue;
                }

                printf("%u, ", k);
                fwrite(&k, sizeof(uint32_t), 1, fp);
                ++k;
            }
            fclose(fp);
            printf("\n");
        }

        // make bitSets
        BitSet bitSet(MAX_INT);
        {
            FILE* fp = fopen(fileName, "rb");
            for (uint32_t j = 0; j < NUM_INTS; ++j) {
                uint32_t k;
                fread(&k, sizeof(uint32_t), 1, fp);
                bitSet.set(k);
            }
            fclose(fp);
        }

        // generate numbers
        {
            printf("generated numbers: ");
            auto enumerator = bitSet.getUnsetEnumerator();
            uint32_t r;
            while (enumerator.next(r)) {
                printf("%u, ", r);
            }
            printf("\n");
        }
    }

    SECTION("N = 1000000000, 10MB") {
        const char* fileName = "integers.dat";
        enum {
            NUM_INTS = 100,     // count of integers stored in the given file
            MAX_INT = 200,      // max integer value
            INTERVAL = 10,      // interval
            NUM_INTERVALS = 20  // count of ranges: [0, 10), [10, 20), ..., [190, 200)
        };

        // make file
        {
            uint32_t k = 0;

            printf("integers: ");
            FILE* fp = fopen(fileName, "wb");
            for (uint32_t i = 0; i < NUM_INTS; ++i) {
                while (isPrime(k)) {
                    ++k;
                    continue;
                }

                printf("%u, ", k);
                fwrite(&k, sizeof(uint32_t), 1, fp);
                ++k;
            }
            fclose(fp);
            printf("\n");
        }

        auto storeBitSet = [](BitSet& bitSet) {
            char fileName[128];
            sprintf(fileName, "bitSet%010u.dat", bitSet.getBase());
            bitSet.store(fileName);
        };

        auto loadBitSet = [](BitSet& bitSet, uint32_t base) {
            char fileName[128];
            sprintf(fileName, "bitSet%010u.dat", base);
            bitSet.load(fileName);
        };

        // make bitSets
        {
            for (int i = 0; i < NUM_INTERVALS; ++i) {
                uint32_t base = INTERVAL * i;
                BitSet bitSet(INTERVAL, base);

                {
                    FILE* fp = fopen(fileName, "rb");
                    for (uint32_t j = 0; j < NUM_INTS; ++j) {
                        uint32_t k;
                        fread(&k, sizeof(uint32_t), 1, fp);

                        if (base <= k && k < base + INTERVAL)
                            bitSet.set(k);

                    }
                    fclose(fp);
                }

                storeBitSet(bitSet);
            }
        }

        // generate numbers
        {
            printf("generated numbers: ");
            for (int i = 0; i < NUM_INTERVALS; ++i) {
                uint32_t base = INTERVAL * i;
                BitSet bitSet;
                loadBitSet(bitSet, base);

                for (uint32_t j = base; j < base + INTERVAL; ++j) {
                    if (!bitSet.isSet(j)) {
                        printf("%d, ", j);
                    }
                }
            }

            printf("\n");
        }
    }
}

} // namespace ex_10_07