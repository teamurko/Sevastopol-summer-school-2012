#include "testlib.h"

using namespace std;

int main()
{
    registerValidation();
    long long n = inf.readLong(1, 1000000000000000000LL);
    inf.readSpace();
    int k = inf.readInt(1, 200);
    inf.readEoln();
    ensure(n >= k);
    for (int i = 0; i < k; ++i) {
        inf.readInt(0, 1000000008);
        if (i + 1 < k) {
            inf.readSpace();
        }
    }
    inf.readEoln();
    inf.readEof();
    return 0;
}
