#include "options.h"
#include "dup_finder.h"

int main(int argc, char *argv[]) {
    options opts;

    int parse_status = opts.parse(argc, argv);
    if (parse_status != 0) {
        return parse_status < 0 ? 0 : parse_status;
    }

    dup_finder comp(opts);
    if (!comp.scan()) {
        return -1;
    }

    comp.compare_dir();
    return 0;
}
