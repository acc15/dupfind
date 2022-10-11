#include <catch2/catch.hpp>

#include <iostream>
#include <string>

#include <damerau_levenshtein.h>

using namespace damerau_levenshtein;

distance_matrix test_dm;

[[nodiscard]] inline size_t dist(const std::string& s1, const std::string& s2) {
    return distance(compute_params<std::string> { s1, s2, DEFAULT_COST, test_dm });
}

[[nodiscard]] inline float factor_of(const std::string& s1, const std::string& s2) {
    auto f = factor<float, std::string>(compute_params<std::string> { s1, s2, DEFAULT_COST, test_dm });
    std::cout << "damerau levenshtein factor between \"" << s1 << "\" and \"" << s2 << "\": " << f << std::endl;
    return f;
}

TEST_CASE( "damerau_levenshtein_distance", "[damerau_levenshtein]" ) {

    // three replace
    REQUIRE(dist("abc", "xyz") == 3 );

    // single remove
    REQUIRE(dist("abba", "aba") == 1 );

    // single transpose
    REQUIRE(dist("abcd", "abdc") == 1 );

    // two transpose
    REQUIRE(dist("abcd", "badc") == 2 );

}

TEST_CASE( "damerau_levenshtein_factor", "[damerau_levenshtein]" ) {

    // three replace
    REQUIRE( factor_of("abc", "abc") == 1.F );

    // single remove
    REQUIRE( factor_of("abba", "aba") == (1.F - (1.F / 7)) );

    // single transpose
    REQUIRE( factor_of("abcd", "abdc") == (1.F - (1.F / 8)) );

    // two transpose
    REQUIRE( factor_of("abcd", "badc") == (1.F - (2.F / 8)) );

}

TEST_CASE( "max_damerau_levenshtein_distance", "[damerau_levenshtein]" ) {
    REQUIRE( max_distance(params { std::string("xyz"), std::string("abcd"), DEFAULT_COST }) == 7 );
}
