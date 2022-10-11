#pragma once

#include <algorithm>

#include "distance_matrix.h"

namespace damerau_levenshtein {

struct cost {
    size_t replace;
    size_t insert;
    size_t remove;
    size_t transpose;
};

const cost DEFAULT_COST = {1, 1, 1, 1};

template <typename T>
struct params {
    const T& l;
    const T& r;
    const struct cost& cost;
};

template <typename Seq>
struct compute_params : params<Seq> {
    distance_matrix& m;
};

template <typename Seq>
size_t max_distance(const params<Seq>& p) {
    return p.l.size() * p.cost.remove + p.r.size() * p.cost.insert;
}

template <typename Seq>
size_t compute_levenshtein_cost(const compute_params<Seq>& p, size_t i, size_t j) {
    return std::min({
        p.m(i - 1, j - 1) + (p.l[i] == p.r[j] ? 0 : p.cost.replace),
        p.m(i - 1, j) + p.cost.remove,
        p.m(i, j - 1) + p.cost.insert
    });
}

template <typename Seq>
size_t compute_damerau_levenshtein_cost(const compute_params<Seq>& p, size_t i, size_t j) {
    const size_t l_cost = compute_levenshtein_cost(p, i, j);
    if (i > 0 && j > 0 && p.l[i] == p.r[j - 1] && p.l[i - 1] == p.r[j]) {
        return std::min(l_cost, p.m(i - 2, j - 2) + p.cost.transpose);
    }
    return l_cost;
}


template <typename Seq>
size_t distance(const compute_params<Seq>& p) {

    typedef typename Seq::value_type value_type;

    size_t ls = p.l.size();
    size_t rs = p.r.size();

    if (ls == 0) {
        return rs * p.cost.insert;
    } else if (rs == 0) {
        return ls * p.cost.remove;
    }

    p.m.init(ls, rs);
    for (size_t i = 0; i < ls; i++) {
        for (size_t j = 0; j < rs; j++) {
            p.m.at(i, j) = compute_damerau_levenshtein_cost(p, i, j);
        }
    }

    return p.m.distance();
}

template <typename T, typename Seq>
T factor(const compute_params<Seq>& p) {
    auto md = max_distance(p);
    auto d = distance(p);
    return static_cast<T>(1.F) - (static_cast<T>(d) / md);
}


}
