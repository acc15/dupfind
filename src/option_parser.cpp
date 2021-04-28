#include <iostream>

#include "option_parser.h"

bool try_parse_float(const std::string& v, float& parsed) {
    if (v.empty()) {
        return false;
    }

    size_t idx;
    float result = std::stof(v, &idx);

    if (idx != v.size()) {
        return false;
    }

    parsed = result;
    return true;
}

option_parser::desc* option_parser::find_desc(const std::string& opt) {
    auto it = _opts.find(opt);
    if (it != _opts.end()) {
        return &it->second;
    }

    auto syn_it = _syn.find(opt);
    if (syn_it != _syn.end()) {
        return syn_it->second;
    }

    return nullptr;
}

void option_parser::error(const err_fn& err) {
    _err = err;
}

bool option_parser::parse_opt(const std::string& opt, const desc* desc, const std::string& value) {
    if (desc == nullptr) {
        if (_err) {
            _err(opt, desc, value);
        }
        return false;
    }
    if (desc->parse(value)) {
        return true;
    }
    if (_err) {
        _err(opt, desc, value);
    }
    return false;
}

bool option_parser::parse(int argc, const char* const argv[]) {

    bool success = true;
    std::string next_opt;
    bool no_more_opts = false;
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);

        if (!next_opt.empty()) {
            success &= parse_opt(next_opt, find_desc(next_opt), arg);
            next_opt.erase();
            continue;
        }

        if (no_more_opts || (arg.size() > 1 && arg[0] != '-')) {
            success &= parse_opt("", find_desc(""), arg);
            continue;
        }

        if (arg.size() == 1) {
            no_more_opts = true;
            continue;
        }

        std::string opt = arg.substr(1);

        const desc* desc = find_desc(opt);
        if (desc == nullptr) {
            if (_err) {
                _err(opt, nullptr, "");
            }
            success = false;
            continue;
        }
        if (!desc->require_arg) {
            success &= parse_opt(opt, desc, "");
        }

        next_opt = opt;
    }
    return true;
}

void option_parser::flag(const std::string& opt, const std::string& description, const std::function<void ()>& parse) {
    _opts[opt] = { description, [=](const std::string& v) { parse(); return true; }, false };
}

void option_parser::opt(const std::string& opt, const std::string& description, const std::function<bool (const std::string&)>& parse) {
    _opts[opt] = { description, parse, true };
}

void option_parser::syn(const std::string& name1, const std::string& name2) {
    _syn[name1] = &_opts[name2];
}

std::ostream& option_parser::print_opts(std::ostream& s) const {
    s << "Opts!!!" << std::endl;
    return s;
}