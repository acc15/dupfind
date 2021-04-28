#pragma once

#include <filesystem>

#include "distance_matrix.h"

class path_comparer {
private:
    distance_matrix _dm;

public:
    float compare(const std::filesystem::path& p1, const std::filesystem::path& p2);

};


