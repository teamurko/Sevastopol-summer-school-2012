#include "testlib.h"

int main()
{
    registerValidation();
    int numTests = inf.readInt(1, 100, "num tests");
    inf.readEoln();
    for (int test = 0; test < numTests; ++test) {
        inf.readLong(1, 1000000000LL * 1000000000LL, "n_i");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
