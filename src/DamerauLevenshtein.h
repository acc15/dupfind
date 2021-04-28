#pragma once

#include "DistanceMatrix.h"

struct DamerauLevenshteinCost {
    size_t replace;
    size_t insert;
    size_t remove;
    size_t transpose;
};

const DamerauLevenshteinCost DEFAULT_COSTS = { 1, 1, 1, 1 };


template <typename Seq>
size_t max_damerau_levenshtein_distance(const Seq& s1, const Seq& s2, const DamerauLevenshteinCost& cost = DEFAULT_COSTS) {
    return s1.size() * cost.remove + s2.size() * cost.insert;
}

template <typename Seq>
size_t damerau_levenshtein_distance(const Seq& s1, const Seq& s2, DistanceMatrix& m, const DamerauLevenshteinCost& cost = DEFAULT_COSTS) {

    typedef typename Seq::value_type value_type;

    size_t l1 = s1.size();
    size_t l2 = s2.size();

    if (l1 == 0) {
        return l2 * cost.insert;
    } else if (l2 == 0) {
        return l1 * cost.remove;
    }

    m.init(l1, l2);
    for (int i = 0; i < l1; i++) {
        for (int j = 0; j < l2; j++) {

            const size_t replace_cost = m(i - 1, j - 1) + (s1[i] == s2[j] ? 0 : cost.replace);
            const size_t remove_cost = m(i - 1, j) + cost.remove;
            const size_t insert_cost = m(i, j - 1) + cost.insert;

            m.at(i, j) = std::min({replace_cost, remove_cost, insert_cost });
            if (i > 0 && j > 0 && s1[i] == s2[j - 1] && s1[i - 1] == s2[j]) {
                m.at(i, j) = std::min( m(i, j), m(i - 2, j - 2) + cost.transpose );
            }

        }
    }

    return m.distance();
}

template <typename T, typename Seq>
T damerau_levenshtein_factor(const Seq& s1, const Seq& s2, DistanceMatrix& m, const DamerauLevenshteinCost& cost = DEFAULT_COSTS) {
    size_t max_distance = max_damerau_levenshtein_distance(s1, s2, cost);
    size_t distance = damerau_levenshtein_distance(s1, s2, m, cost);
    return static_cast<T>(1.) - (static_cast<T>(distance) / max_distance);
}


