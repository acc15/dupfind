#pragma once

#include <bitset>
#include <filesystem>

#include "PatternSet.h"

enum OptionFlags {

    NO_FILE,
    NO_DIR,
    NO_MIX,
    NO_SAME_DIR,
    OPTION_FLAG_LAST

};

class Options {
public:
    std::filesystem::path dir;
    std::bitset<OPTION_FLAG_LAST> flags;
    PatternSet file_patterns;
    PatternSet dir_patterns;
    PatternSet patterns;
    float factor;

    Options();

    [[nodiscard]] bool cmp_files() const;
    [[nodiscard]] bool cmp_dirs() const;
    [[nodiscard]] bool cmp_mixed() const;
    [[nodiscard]] bool skip_same_dir() const;

    [[nodiscard]] bool dir_match(const std::filesystem::path& p) const;
    [[nodiscard]] bool file_match(const std::filesystem::path& p) const;

    bool parse(int argc, const char* const argv[]);

};


