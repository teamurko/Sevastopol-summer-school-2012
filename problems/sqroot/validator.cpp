#include "testlib.h"

using namespace std;

bool isPrime(int n)
{
    if (n <= 1) return false;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) return false;
    }
    return true;
}

int gcd(int a, int b)
{
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main() {
    registerValidation();

    int numTests = inf.readInt(1, 100000);
    inf.readEoln();
    for (int i = 0; i < numTests; ++i) {
        int a = inf.readInt(1, 32767);
        inf.readSpace();
        int n = inf.readInt(1, 32767);
        ensure(isPrime(n));
        ensure(gcd(n, a) == 1);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
