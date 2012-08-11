#include "testlib.h"
#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b)
{
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

std::vector<ll> factorize(ll n)
{
    std::vector<ll> result;
    for (int p = 2; p * p <= n; ++p) {
        while (n % p == 0) {
            result.push_back(p);
            n /= p;
        }
    }
    if (n > 1) {
        result.push_back(n);
    }
    return result;
}

int main()
{
    registerValidation();
    int numTests = inf.readInt(1, 10000, "num tests");
    inf.readEoln();
    for (int test = 0; test < numTests; ++test) {
        //TODO increase limits
        int e = inf.readInt(1, 32000);
        inf.readSpace();
        int n = inf.readInt(1, 32000);
        vector<ll> f = factorize(n);
        ensure(f.size() == 2);
        ensure(f.front() != f.back());
        ensure(f.front() > 2);
        ensure(f.back() > 2);
        ll phi = (f.front() - 1) * (f.back() - 1);
        ensure(gcd(phi, e) == 1);
        inf.readSpace();
        int c = inf.readInt(0, 32000);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
