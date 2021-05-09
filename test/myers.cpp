#include <catch2/catch.hpp>

#include <string>

#include "myers.h"

[[nodiscard]] inline size_t dist(const std::string &s1, const std::string &s2) {
    return myers_distance(s1, s2);
}

TEST_CASE("myers_distance", "[myers]") {

//    REQUIRE(dist("abba", "abba") == 0);
//
//    // three delete + three add
//    REQUIRE(dist("abc", "xyz") == 6);
//
//    // single remove of second 'b'
//    REQUIRE(dist("abba", "aba") == 1);
//
//    // 2 remove cd + 2 add dc
//    REQUIRE(dist("abcd", "abdc") == 4);
//
//    // maximum diff - 4 remove, 4 insert
//    REQUIRE(dist("abcd", "badc") == 8);

}
