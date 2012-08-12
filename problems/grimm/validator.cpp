#include "testlib.h"

using namespace std;

bool isPrime(int n)
{
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int main()
{
    registerValidation();
    int a = inf.readInt(2, 1000 * 1000 * 1000);
    inf.readSpace();
    int b = inf.readInt(2, 1000 * 1000 * 1000);
    inf.readEoln();
    inf.readEof();
    ensure(isPrime(a));
    ensure(isPrime(b));
    for (int i = a + 1; i < b; ++i) {
        ensure(!isPrime(i));
    }
    return 0;
}
