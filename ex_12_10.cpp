//
// Created by blazeq on 2017. 11. 17..
//

#include <iostream>
#include "catch.hpp"

namespace ex_12_10 {

void* aligned_malloc(size_t requiredBytes, size_t alignment) {
    size_t offset = alignment - 1 + sizeof(void*);
    void* p1 = malloc(offset + requiredBytes);
    if (p1 == nullptr)
        return nullptr;

    void* p2 = (void*)((((size_t)(p1)) + offset) & ~(alignment - 1));
    ((void**)p2)[-1] = p1;
    return p2;
}

void aligned_free(void* p2) {
    void* p1 = ((void**)p2)[-1];
    free(p1);
}

TEST_CASE("12-10", "[12-10]") {
    void* p = aligned_malloc(100, 16);
    REQUIRE(((size_t)(p)) % 16 == 0);
    aligned_free(p);
}

} // namespace ex_12_10