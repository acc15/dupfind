#include "options.h"
#include "dup_finder.h"

int main(int argc, char *argv[]) {
    options opts;
    opts.parse(argc, argv);

    dup_finder comp(opts);
    if (!comp.scan()) {
        return -1;
    }
    comp.compare_dir();
    return 0;
}
