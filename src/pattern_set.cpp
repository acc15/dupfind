#include "pattern_set.h"

bool pattern_set::include(const std::string& re) {
    try {
        _include.emplace_back(make_pattern_pair(re));
        return true;
    } catch (const std::regex_error& e) {
        return false;
    }
}

bool pattern_set::exclude(const std::string& re) {
    try {
        _exclude.emplace_back(make_pattern_pair(re));
        return true;
    } catch (const std::regex_error& e) {
        return false;
    }
}

bool pattern_set::match(const std::string& str) const {
    for (const PatternPair& ip: _include) {
        if (std::regex_match(str, ip.first)) {
            return true;
        }
    }
    for (const PatternPair& ep: _exclude) {
        if (std::regex_match(str, ep.first)) {
            return false;
        }
    }
    return _include.empty() || !_exclude.empty();
}

std::ostream& operator<<(std::ostream& o, const pattern_set& p) {
    o << "{";
    for (const pattern_set::PatternPair& ip: p._include) {
        o << "+(" << ip.second << ")";
    }
    for (const pattern_set::PatternPair& ep: p._exclude) {
        o << "-(" << ep.second << ")";
    }
    o << "}";
    return o;
}



pattern_set::PatternPair pattern_set::make_pattern_pair(const std::string& str) {
    return std::make_pair(make_regex(str), str);
}

std::regex pattern_set::make_regex(const std::string& str) {
    if (str.starts_with("(?i)")) {
        std::string re_str = str.substr(4);
        return std::regex(re_str, std::regex_constants::icase);
    } else {
        return std::regex(str);
    }
}
