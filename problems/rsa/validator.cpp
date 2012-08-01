#include "testlib.h"

using namespace std;

int main()
{
    registerValidation();
    int numTests = inf.readInt(1, 2000, "num tests");
    inf.readEoln();
    for (int test = 0; test < numTests; ++test) {
        //TODO increase limits
        int e = inf.readInt(1, 32000);
        inf.readSpace();
        int n = inf.readInt(1, 32000);
        inf.readSpace();
        int c = inf.readInt(1, 32000);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
