#pragma once

#include <bitset>
#include <filesystem>

#include "pattern_set.h"

enum option_flags {

    NO_FILE,
    NO_DIR,
    NO_MIX,
    NO_SAME_DIR,
    OPTION_FLAG_LAST

};

class options {
public:
    std::filesystem::path dir;
    std::bitset<OPTION_FLAG_LAST> flags;
    pattern_set file_patterns;
    pattern_set dir_patterns;
    pattern_set patterns;
    float factor;

    options();

    [[nodiscard]] bool cmp_files() const;
    [[nodiscard]] bool cmp_dirs() const;
    [[nodiscard]] bool cmp_mixed() const;
    [[nodiscard]] bool skip_same_dir() const;

    [[nodiscard]] bool dir_match(const std::filesystem::path& p) const;
    [[nodiscard]] bool file_match(const std::filesystem::path& p) const;

    int parse(int argc, const char* const argv[]);

};


