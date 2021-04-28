#include <catch2/catch.hpp>

#include <dup_finder.h>

TEST_CASE( "dup_finder", "[dup_finder]" ) {

    REQUIRE( dup_finder::compute_comparison_count(0) == 0 );
    REQUIRE( dup_finder::compute_comparison_count(1) == 0 );
    REQUIRE( dup_finder::compute_comparison_count(2) == 1 );
    REQUIRE( dup_finder::compute_comparison_count(5) == 10 );
    REQUIRE( dup_finder::compute_comparison_count(6) == 15 );

}
