#pragma once

#include <regex>
#include <ostream>

class pattern_set {
private:
    typedef std::pair<std::regex, std::string> pair;

    std::vector<pair> _include;
    std::vector<pair> _exclude;

    static pair make_pattern_pair(const std::string& str);
    static std::regex make_regex(const std::string& str);

public:

    bool include(const std::string& re);
    bool exclude(const std::string& re);

    [[nodiscard]] bool match(const std::string& str) const;

    friend std::ostream& operator<<(std::ostream& o, const pattern_set& p);

};

std::ostream& operator<<(std::ostream& o, const pattern_set& p);

