#include <iostream>

#include "options.h"
#include "option_parser.h"

options::options() : dir(std::filesystem::current_path()), factor(0.9f) {
}

bool options::cmp_files() const {
    return !flags.test(NO_FILE);
}

bool options::cmp_dirs() const {
    return !flags.test(NO_DIR);
}

bool options::cmp_mixed() const {
    return !flags.test(NO_MIX);
}

bool options::skip_same_dir() const {
    return flags.test(NO_SAME_DIR);
}

bool options::dir_match(const std::filesystem::path& p) const {
    const std::string p_str = p.string();
    return cmp_dirs() && patterns.match(p_str) && dir_patterns.match(p_str);
}

bool options::file_match(const std::filesystem::path& p) const {
    const std::string p_str = p.string();
    return cmp_files() && patterns.match(p_str) && file_patterns.match(p_str);
}

int options::parse(int argc, const char* const* argv) {

    option_parser p;

    bool usage = false;

    p.flag("h", "Prints this help", [&usage]() { usage = true; });

    p.opt({"d", ""}, "Directory to scan", [this](const std::string& val) { dir = val; return true; });
    p.opt("f", "Minimum factor", [this](const std::string& val) { return try_parse_float(val, factor); });

    p.flag("nf", "Exclude all files from comparison", [this]() { flags.set(NO_FILE); });
    p.flag("nd", "Exclude all directories from comparison", [this]() { flags.set(NO_DIR); });
    p.flag("nm", "Disable mixed comparisons (file vs dir)", [this]() { flags.set(NO_MIX); });
    p.flag("ns", "Disable file/dir comparisons in same directory", [this]() { flags.set(NO_SAME_DIR); });

    p.opt("i", "Common inclusion regex", [this](const std::string& val) { return patterns.include(val); });
    p.opt("e", "Common exclusion regex", [this](const std::string& val) { return patterns.exclude(val); });
    p.opt("if", "File inclusion regex", [this](const std::string& val) { return file_patterns.include(val); });
    p.opt("ef", "File exclusion regex", [this](const std::string& val) { return file_patterns.exclude(val); });
    p.opt("id", "Dir inclusion regex", [this](const std::string& val) { return dir_patterns.include(val); });
    p.opt("ed", "Dir exclusion regex", [this](const std::string& val) { return dir_patterns.exclude(val); });

    bool success = p.parse(argc, argv);
    if (usage) {
        p.print_opts(std::cout);
        return -1;
    }
    return success ? 0 : 1;

}

