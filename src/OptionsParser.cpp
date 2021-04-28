#include "OptionsParser.h"

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

OptionsParser::Desc* OptionsParser::find_desc(const std::string& opt) {
    auto it = _opts.find(opt);
    if (it == _opts.end()) {
        return nullptr;
    }
    return &it->second;
}

bool OptionsParser::parse(int argc, const char* const argv[]) {

    const Desc* next_desc = nullptr;
    bool no_more_opts = false;
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);

        if (next_desc != nullptr) {
            next_desc->parse(arg);
            next_desc = nullptr;
            continue;
        }

        if (no_more_opts || (arg.size() > 1 && arg[0] != '-')) {
            const Desc* desc = find_desc("");
            if (desc != nullptr) {
                desc->parse(arg);
            }
            continue;
        }

        if (arg.size() == 1) {
            no_more_opts = true;
            continue;
        }

        std::string opt = arg.substr(1);

        const Desc* desc = find_desc(opt);
        if (desc == nullptr) {
            continue;
        }

        if (desc->require_arg) {
            next_desc = desc;
        } else {
            desc->parse("");
        }

    }
    return true;

}

void OptionsParser::flag(const std::string& opt, const std::string& description, const std::function<void ()>& parse) {
    _opts[opt] = { description, [=](const std::string& v) { parse(); return true; }, false };
}

void OptionsParser::opt(const std::string& opt, const std::string& description, const std::function<bool (const std::string&)>& parse) {
    _opts[opt] = { description, parse, true };
}

void OptionsParser::syn(const std::string& name1, const std::string& name2) {
    _opts[name1] = _opts[name2];
}