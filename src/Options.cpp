#include <cstring>

#include "Options.h"
#include "OptionsParser.h"

Options::Options() : dir(std::filesystem::current_path()), factor(0.9f) {
}

bool Options::cmp_files() const {
    return !flags.test(NO_FILE);
}

bool Options::cmp_dirs() const {
    return !flags.test(NO_DIR);
}

bool Options::cmp_mixed() const {
    return !flags.test(NO_MIX);
}

bool Options::skip_same_dir() const {
    return flags.test(NO_SAME_DIR);
}

bool Options::dir_match(const std::filesystem::path& p) const {
    return cmp_dirs() && patterns.match(p) && dir_patterns.match(p);
}

bool Options::file_match(const std::filesystem::path& p) const {
    return cmp_files() && patterns.match(p) && file_patterns.match(p);
}

bool Options::parse(int argc, const char* const* argv) {
    OptionsParser p;

    p.flag("nf", "Exclude all files from comparison", [this]() { flags.set(NO_FILE); });
    p.flag("nd", "Exclude all directories from comparison", [this]() { flags.set(NO_DIR); });
    p.flag("nm", "Disable mixed comparisons (file vs dir)", [this]() { flags.set(NO_MIX); });
    p.flag("ns", "Disable file/dir comparisons in same directory", [this]() { flags.set(NO_SAME_DIR); });

    p.opt("f", "Minimum factor", [this](const std::string& val) { return try_parse_float(val, factor); });

    p.opt("d", "Directory to scan", [this](const std::string& val) { dir = val; return true; });
    p.syn("", "d");

    p.opt("i", "Inclusion regex", [this](const std::string& val) { return patterns.include(val); });
    p.opt("e", "Exclusion regex", [this](const std::string& val) { return patterns.exclude(val); });
    p.opt("if", "File inclusion regex", [this](const std::string& val) { return file_patterns.include(val); });
    p.opt("ef", "File exclusion regex", [this](const std::string& val) { return file_patterns.exclude(val); });
    p.opt("id", "Dir inclusion regex", [this](const std::string& val) { return dir_patterns.include(val); });
    p.opt("ed", "Dir exclusion regex", [this](const std::string& val) { return dir_patterns.exclude(val); });

    return p.parse(argc, argv);
}

