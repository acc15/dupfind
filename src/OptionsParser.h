#pragma once

#include <string>
#include <unordered_map>
#include <functional>

bool try_parse_float(const std::string& str, float& result);

class OptionsParser {
public:
    struct Desc {
        std::string description;
        std::function<bool (const std::string&)> parse;
        bool require_arg;
    };

private:

    typedef std::unordered_map<std::string, Desc> OptionMap;
    OptionMap _opts;

public:

    Desc* find_desc(const std::string& opt);

    void flag(const std::string& name, const std::string& description, const std::function<void ()>& parse);
    void opt(const std::string& name, const std::string& description, const std::function<bool (const std::string&)>& parse);
    void syn(const std::string& name1, const std::string& name2);

    bool parse(int argc, const char* const argv[]);

};


