#include <cassert>

#include "distance_matrix.h"

size_t distance_matrix::operator()(size_t i, size_t j) const {
    if (i == npos) {
        return j + 1;
    } else if (j == npos) {
        return i + 1;
    }
    return _v[index(i, j)];
}

size_t& distance_matrix::at(size_t i, size_t j) {
    assert( j < _c && i < _v.size() / _c );
    return _v[index(i, j)];
}

size_t distance_matrix::index(size_t i, size_t j) const {
    return i * _c + j;
}

size_t distance_matrix::distance() const {
    return _v[_v.size() - 1];
}

void distance_matrix::init(size_t rows, size_t cols) {
    assert(rows > 0 && cols > 0);
    _c = cols;
    _v.resize(rows * cols);
}