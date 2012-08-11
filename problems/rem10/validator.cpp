#include "testlib.h"
using namespace std;

bool isPrime(int n)
{
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int main()
{
    registerValidation();
    int k = inf.readInt(7, 100);
    ensure(isPrime(k));
    inf.readSpace();
    int n = inf.readInt(1, 100);
    inf.readEoln();
    inf.readEof();
    return 0;
}
