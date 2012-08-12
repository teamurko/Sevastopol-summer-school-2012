#include "testlib.h"
#include <set>

using namespace std;

bool isPrime(int n)
{
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int main(int argc, char * argv[])
{
    registerTestlibCmd(argc, argv);
    int l = inf.readInt();
    int r = inf.readInt();
    int n = r - l - 1;
    set<int> used;
    for (int i = 0; i < n; ++i) {
        int x = ouf.readInt();
        if (used.count(x)) {
            quitf(_wa, "primes should be unique, %d occures two times", x);
        }
        used.insert(x);
        if (!isPrime(x)) {
            quitf(_wa, "%d should be a prime number", x);
        }
        if ((l + i + 1) % x != 0) {
            quitf(_wa, "%d should be a divisor of %d", x, l + i + 1);
        }
    }
    quitf(_ok, "good job!");
    return 0;
}
