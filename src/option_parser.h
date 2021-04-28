#pragma once

#include <string>
#include <unordered_map>
#include <functional>

bool try_parse_float(const std::string& str, float& result);




class option_parser {
public:
    struct desc {
        std::string description;
        std::function<bool (const std::string&)> parse;
        bool require_arg;
    };

    typedef std::function<void(const std::string&, const desc*, const std::string&)> err_fn;

private:

    typedef std::unordered_map<std::string, desc> desc_map;
    typedef std::unordered_map<std::string, desc*> syn_map;

    desc_map _opts;
    syn_map _syn;
    err_fn _err;

    bool parse_opt(const std::string& opt, const desc* desc, const std::string& value);

public:

    desc* find_desc(const std::string& opt);

    void error(const err_fn& err);

    void flag(const std::string& name, const std::string& description, const std::function<void ()>& parse);
    void opt(const std::string& name, const std::string& description, const std::function<bool (const std::string&)>& parse);
    void syn(const std::string& name1, const std::string& name2);

    bool parse(int argc, const char* const argv[]);

    std::ostream& print_opts(std::ostream& s) const;

};


