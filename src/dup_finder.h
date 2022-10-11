#pragma once

#include <cstddef>
#include <filesystem>
#include "options.h"
#include "path_comparer.h"

class dup_finder {

private:
    std::vector<std::filesystem::path> _fp;
    std::vector<std::filesystem::path> _dp;

    path_comparer _pc;

    size_t _excluded_file_comparisons;
    size_t _excluded_mixed_comparisons;
    size_t _excluded_dir_comparisons;
    size_t _comparison_count;

    const options& _opts;

    void scan_dir(const std::filesystem::path& path);
    void compare(const std::filesystem::path& e1, const std::filesystem::path& e2);

public:

    explicit dup_finder(const options& opts);

    bool scan();
    void compare_dir();

    static size_t compute_comparison_count(size_t n);

};


