#include "PatternSet.h"

bool PatternSet::include(const std::string& re) {
    try {
        _include.emplace_back(make_pattern_pair(re));
        return true;
    } catch (const std::regex_error& e) {
        return false;
    }
}

bool PatternSet::exclude(const std::string& re) {
    try {
        _exclude.emplace_back(make_pattern_pair(re));
        return true;
    } catch (const std::regex_error& e) {
        return false;
    }
}

bool PatternSet::match(const std::string& str) const {
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

std::ostream& operator<<(std::ostream& o, const PatternSet& p) {
    o << "{";
    for (const PatternSet::PatternPair& ip: p._include) {
        o << "+(" << ip.second << ")";
    }
    for (const PatternSet::PatternPair& ep: p._exclude) {
        o << "-(" << ep.second << ")";
    }
    o << "}";
    return o;
}



PatternSet::PatternPair PatternSet::make_pattern_pair(const std::string& str) {
    return std::make_pair(make_regex(str), str);
}

std::regex PatternSet::make_regex(const std::string& str) {
    if (str.starts_with("(?i)")) {
        std::string re_str = str.substr(4);
        return std::regex(re_str, std::regex_constants::icase);
    } else {
        return std::regex(str);
    }
}
