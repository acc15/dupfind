#include <catch2/catch.hpp>

#include <Options.h>
#include <OptionsParser.h>

TEST_CASE("parse_float", "[options]") {


    float f1 = 0.0f;
    REQUIRE_FALSE( try_parse_float("0.15xxx", f1) );
    REQUIRE( f1 == 0.0f );

    REQUIRE( try_parse_float("0.15", f1) );
    REQUIRE( f1 == 0.15f );

    REQUIRE( try_parse_float("0.5", f1) );
    REQUIRE( f1 == 0.5f );

}

TEST_CASE("options", "[options]") {

    Options opts;

    const char* const cmd[] = { "test.exe", "-f", "0.5", "-nd", "my_dir", "-if", ".*\\.mp4", "-ns" };
    opts.parse(std::size(cmd), cmd);

    REQUIRE( opts.cmp_mixed() );
    REQUIRE( opts.cmp_files() );
    REQUIRE_FALSE( opts.cmp_dirs() );
    REQUIRE( opts.dir == "my_dir" );
    REQUIRE( opts.factor == 0.5f );
    REQUIRE(opts.skip_same_dir() );

    REQUIRE( opts.file_patterns.match("1.  Test, Mega test (5000p).mp4") );
    REQUIRE_FALSE( opts.file_patterns.match("2. test.mp3") );

}