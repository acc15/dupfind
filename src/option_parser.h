#pragma once

#include <string>
#include <unordered_map>
#include <functional>

bool try_parse_float(const std::string& str, float& result);

class option_names {
private:
    std::vector<std::string> _vec;
public:
    option_names() = default;
    option_names(const option_names& other) = default;
    option_names(option_names&& other) = default;

    option_names(const char* str);
    option_names(const std::string& str);
    option_names(const std::initializer_list<std::string>& init);

    void add(const std::string& name);
    [[nodiscard]] const std::vector<std::string>& vec() const;
};

struct option_desc {
    option_names names;
    std::string description;
    std::function<bool (const std::string&)> parse;
    bool require_arg;
};

class option_parser {
public:
    typedef std::function<void(const std::string&, const option_desc*, const std::string&)> err_fn;

private:

    std::vector<option_desc> _opts;
    std::unordered_map<std::string, size_t> _opt_index;
    err_fn _err;

    bool parse_opt(const std::string& opt, const option_desc* desc, const std::string& value);

public:

    option_desc* find_desc(const std::string& opt);

    void error(const err_fn& err);

    void flag(const option_names& names, const std::string& description, const std::function<void ()>& parse);
    void opt(const option_names& names, const std::string& description, const std::function<bool (const std::string&)>& parse);
    void desc(const option_desc& desc);
    void syn(const std::string& name1, const std::string& name2);

    bool parse(int argc, const char* const argv[]);

    std::ostream& print_opts(std::ostream& s) const;

};


