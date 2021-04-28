#include <cassert>

#include "DistanceMatrix.h"

size_t DistanceMatrix::operator()(size_t i, size_t j) const {
    if (i == npos) {
        return j + 1;
    } else if (j == npos) {
        return i + 1;
    }
    return _v[index(i, j)];
}

size_t& DistanceMatrix::at(size_t i, size_t j) {
    assert( j < _c && i < _v.size() / _c );
    return _v[index(i, j)];
}

size_t DistanceMatrix::index(size_t i, size_t j) const {
    return i * _c + j;
}

size_t DistanceMatrix::distance() const {
    return _v[_v.size() - 1];
}

void DistanceMatrix::init(size_t rows, size_t cols) {
    assert(rows > 0 && cols > 0);
    _c = cols;
    _v.resize(rows * cols);
}