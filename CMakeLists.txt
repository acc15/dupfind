cmake_minimum_required(VERSION 3.19)
project(dupfind)

set(CMAKE_CXX_STANDARD 20)

set(MAIN_SRC
    src/option_parser.h
    src/option_parser.cpp
    src/options.cpp
    src/options.h
    src/dup_finder.cpp
    src/dup_finder.h
    src/damerau_levenshtein.h
    src/distance_matrix.h
    src/distance_matrix.cpp
    src/pattern_set.cpp
    src/pattern_set.h
    src/path_comparer.cpp
    src/path_comparer.h
)

add_executable(dupfind ${MAIN_SRC} src/main.cpp)

find_package(Catch2 REQUIRED)

add_executable(dupfind_tests
    ${MAIN_SRC}
    test/damerau_levenshtein.cpp
    test/options.cpp
    test/main.cpp
    test/dup_finder.cpp
)
target_include_directories(dupfind_tests PRIVATE src)
target_link_libraries(dupfind_tests PRIVATE Catch2::Catch2)
