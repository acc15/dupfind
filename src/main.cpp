#include "Options.h"
#include "DupFind.h"

int main(int argc, char *argv[]) {

    Options opts;
    opts.parse(argc, argv);

    DupFind comp(opts);
    if (!comp.scan()) {
        return -1;
    }
    comp.compare_dir();
    return 0;
}
