#include <catch2/catch.hpp>

#include <DupFind.h>

TEST_CASE( "DupFind", "[DupFind]" ) {

    REQUIRE( DupFind::compute_comparison_count(0) == 0 );
    REQUIRE( DupFind::compute_comparison_count(1) == 0 );
    REQUIRE( DupFind::compute_comparison_count(2) == 1 );
    REQUIRE( DupFind::compute_comparison_count(5) == 10 );
    REQUIRE( DupFind::compute_comparison_count(6) == 15 );

}
