#include <iostream>
#include <vector>

#include "dup_finder.h"

namespace fs = std::filesystem;

void dup_finder::compare(const fs::path& e1, const fs::path& e2) {
    auto factor = _pc.compare(e1, e2);
    if (factor >= _opts.factor) {
        std::cout << "[" << std::setfill('0') << std::setw(10) << _comparison_count << "][";
        if (factor >= 1.f) {
            std::cout << "FULL MATCH";
        } else {
            std::cout << std::fixed << std::setprecision(8) << factor;
        }
        std::cout << "] " << e1 << " vs " << e2 << std::endl;
    }
    ++_comparison_count;
}

void dup_finder::scan_dir(const fs::path& path) {

    size_t file_count = 0;
    size_t dir_count = 0;
    for (const fs::directory_entry& e: fs::directory_iterator(path)) {
        if (e.is_directory()) {
            if (_opts.cmp_dirs() && _opts.dir_match(e.path().filename())) {
                _dp.push_back(fs::relative(e.path(), _opts.dir));
                ++dir_count;
            }
            scan_dir(e.path());
        } else if (_opts.file_match(e.path().filename())) {
            _fp.push_back(fs::relative(e.path(), _opts.dir));
            ++file_count;
        }
    }

    if (_opts.skip_same_dir()) {
        _excluded_file_comparisons += compute_comparison_count(file_count);
        _excluded_dir_comparisons += compute_comparison_count(dir_count);
        _excluded_mixed_comparisons += path == _opts.dir ? 0 : file_count;
    }

}

bool dup_finder::scan() {

    std::cout << "Scanning directory: " << _opts.dir << std::endl;
    std::cout << "Files: " << (_opts.cmp_files() ? "on" : "off") << std::endl;
    std::cout << "Dirs: " << (_opts.cmp_dirs() ? "on" : "off") << std::endl;
    std::cout << "Mixed: " << (_opts.cmp_mixed() ? "on" : "off") << std::endl;
    std::cout << "File patterns: " << _opts.file_patterns << std::endl;
    std::cout << "Dir patterns: " << _opts.dir_patterns << std::endl;
    std::cout << std::endl;

    _excluded_file_comparisons = 0;
    _excluded_mixed_comparisons = 0;
    _excluded_dir_comparisons = 0;
    _comparison_count = 0;

    _dp.clear();
    _fp.clear();

    if (!fs::is_directory(_opts.dir)) {
        std::cout << "Directory " << _opts.dir << " doesn't exists";
        return false;
    }

    scan_dir(_opts.dir);

    size_t file_comparisons = compute_comparison_count(_fp.size()) - _excluded_file_comparisons;
    size_t dir_comparisons = compute_comparison_count(_dp.size()) - _excluded_dir_comparisons;
    size_t mixed_comparisons = _fp.empty() || _dp.empty() ? 0 : _fp.size() * _dp.size() - _excluded_mixed_comparisons;
    size_t total_comparisons = file_comparisons + dir_comparisons + mixed_comparisons;

    std::cout << "Directory scan completed" << std::endl
              << std::endl
              << "=== Totals ===" << std::endl
              << "Files: " << _fp.size() << std::endl
              << "Dirs: " << _dp.size() << std::endl
              << "File comparisons: " << file_comparisons << std::endl
              << "Dir comparisons: " << dir_comparisons << std::endl
              << "Mixed comparisons: " << mixed_comparisons << std::endl
              << "Total comparisons: " << total_comparisons << std::endl
              << std::endl;

    return true;
}


void dup_finder::compare_dir() {

    for (size_t i = 0; i < _fp.size(); ++i) {
        const auto& f1 = _fp[i];
        for (size_t j = i + 1; j < _fp.size(); ++j) {
            const auto& f2 = _fp[j];
            if (_opts.skip_same_dir() && f1.parent_path() == f2.parent_path()) {
                continue;
            }
            compare(f1, f2);
        }

        if (!_opts.cmp_mixed()) {
            continue;
        }

        for (const fs::path& dir: _dp) {
            if (_opts.skip_same_dir() && f1.parent_path() == dir) {
                continue;
            }
            compare(f1, dir);
        }
    }

    for (size_t i = 0; i < _dp.size(); ++i) {
        const auto& d1 = _dp[i];
        for (size_t j = i + 1; j < _dp.size(); ++j) {
            const auto& d2 = _dp[j];
            if (_opts.skip_same_dir() && d1.parent_path() == d2.parent_path()) {
                continue;
            }
            compare(d1, d2);
        }
    }
}

dup_finder::dup_finder(const options& opts) : _opts(opts)
    , _excluded_dir_comparisons(0)
    , _excluded_mixed_comparisons(0)
    , _excluded_file_comparisons(0)
    , _comparison_count(0)
{
}

size_t dup_finder::compute_comparison_count(size_t n) {
    return (n * n - n) / 2;
}


