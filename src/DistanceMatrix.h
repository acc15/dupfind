#pragma once

#include <cstddef>
#include <vector>

struct DistanceMatrix {
public:
    static const size_t npos = -1;

    [[nodiscard]] size_t operator()(size_t i, size_t j) const;
    [[nodiscard]] size_t& at(size_t i, size_t j);
    [[nodiscard]] size_t index(size_t i, size_t j) const;
    [[nodiscard]] size_t distance() const;
    void init(size_t rows, size_t cols);

private:
    std::vector<size_t> _v;
    size_t _c;

};

