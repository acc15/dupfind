cmake_minimum_required(VERSION 3.19)
project(dupfind)

set(CMAKE_CXX_STANDARD 20)

set(MAIN_SRC
    src/OptionsParser.h
    src/OptionsParser.cpp
    src/Options.cpp
    src/Options.h
    src/DupFind.cpp
    src/DupFind.h
    src/DamerauLevenshtein.h
    src/DistanceMatrix.h
    src/DistanceMatrix.cpp
    src/PatternSet.cpp
    src/PatternSet.h
)

add_executable(dupfind ${MAIN_SRC} src/main.cpp)

find_package(Catch2 REQUIRED)

set(TEST_SRC
    ${MAIN_SRC}
    test/DamerauLevenshtein.cpp
    test/Options.cpp
    test/main.cpp
    test/DupFind.cpp
)

add_executable(dupfind_tests ${TEST_SRC})
target_include_directories(dupfind_tests PRIVATE src)
target_link_libraries(dupfind_tests PRIVATE Catch2::Catch2)
