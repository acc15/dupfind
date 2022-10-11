#include "path_comparer.h"
#include "damerau_levenshtein.h"

float path_comparer::compare(const std::filesystem::path& p1, const std::filesystem::path& p2) {
    return damerau_levenshtein::factor<float, std::string>(damerau_levenshtein::compute_params<std::string> {
        p1.filename().string(),
        p2.filename().string(),
        damerau_levenshtein::DEFAULT_COST,
        _dm
    });
}
