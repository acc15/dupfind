#include "path_comparer.h"
#include "damerau_levenshtein.h"

float path_comparer::compare(const std::filesystem::path& p1, const std::filesystem::path& p2) {
    return damerau_levenshtein_factor<float>(p1.filename().string(), p2.filename().string(), _dm);
}
