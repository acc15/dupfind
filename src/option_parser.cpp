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

option_names::option_names(const char* str): option_names(std::string(str)) {
}

option_names::option_names(const std::string& name) {
    add(name);
}

option_names::option_names(const std::initializer_list<std::string>& init): _vec(init) {
}

void option_names::add(const std::string& name) {
    _vec.push_back(name);
}

const std::vector<std::string>& option_names::vec() const {
    return _vec;
}

option_desc* option_parser::find_desc(const std::string& opt) {
    auto it = _opt_index.find(opt);
    return it != _opt_index.end() ? &_opts[it->second] : nullptr;
}

void option_parser::error(const err_fn& err) {
    _err = err;
}

bool option_parser::parse_opt(const std::string& opt, const option_desc* desc, const std::string& value) {
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

        const option_desc* desc = find_desc(opt);
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

void option_parser::flag(const option_names& names, const std::string& description, const std::function<void ()>& parse) {
    desc({names, description, [=](const std::string& v) { parse(); return true; }, false });
}

void option_parser::opt(const option_names& names, const std::string& description, const std::function<bool (const std::string&)>& parse) {
    desc({names, description, parse, true });
}

void option_parser::desc(const option_desc& desc) {
    _opts.push_back(desc);
    for (const std::string& n: desc.names.vec()) {
        _opt_index[n] = _opts.size() - 1;
    }
}

void option_parser::syn(const std::string& name1, const std::string& name2) {
    const auto it = _opt_index.find(name2);
    if (it == _opt_index.end()) {
        return;
    }
    _opts[it->second].names.add(name1);
    _opt_index[name1] = it->second;
}

std::ostream& option_parser::print_opts(std::ostream& s) const {
    for (const option_desc& d: _opts) {
        const std::vector<std::string>& names = d.names.vec();
        for (size_t i = 0; i < names.size(); i++) {
            const std::string& name = names[i];
            if (i > 0) {
                s << ",";
            }
            if (name.empty()) {
                s << "<unnamed>";
            } else {
                s << "-" << name;
            }
        }
        s << " - " << d.description << std::endl;
    }
    return s;
}