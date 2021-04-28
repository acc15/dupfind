#pragma once

#include <cstddef>
#include <filesystem>
#include "Options.h"
#include "DistanceMatrix.h"

class DupFind {

private:
    DistanceMatrix _dm;
    std::vector<std::filesystem::path> _fp;
    std::vector<std::filesystem::path> _dp;

    size_t _excluded_file_comparisons;
    size_t _excluded_mixed_comparisons;
    size_t _excluded_dir_comparisons;
    size_t _comparison_count;

    const Options& _opts;

    void scan_dir(const std::filesystem::path& path);

public:

    explicit DupFind(const Options& opts);

    bool scan();
    void compare_dir();
    void compare(const std::filesystem::path& e1, const std::filesystem::path& e2);

    static size_t compute_comparison_count(size_t n);

};


