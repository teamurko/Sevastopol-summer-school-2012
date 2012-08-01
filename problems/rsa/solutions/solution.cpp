#include <iostream>
#include <cassert>
#include <vector>
typedef long long ll;

ll gcd(ll a, ll b, ll& x, ll& y)
{
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll xx, yy;
    ll d = gcd(b % a, a, xx, yy);
    x = yy - b / a * xx;
    y = xx;
    return d;
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

ll pow(ll x, ll n, ll m)
{
    ll zweip = x;
    ll res = 1 % m;
    while (n > 0) {
        if (n & 1) res = (res * zweip) % m;
        zweip *= zweip;
        zweip %= m;
        n >>= 1;
    }
    return res;
}

int main (int argc, char * const argv[])
{
    int numTests; std::cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        ll e, n, c; std::cin >> e >> n >> c;
        std::vector<ll> fact = factorize(n);
        assert(fact.size() == 2);
        assert(fact.front() != fact.back());
        ll phi = (fact[0] - 1) * (fact[1] - 1);
        ll x, y;
        assert(gcd(e, phi, x, y) == 1);
        x = (x % phi + phi) % phi;
        assert((x * e) % phi == 1);
        std::cout << pow(c, x, n) << std::endl;
    }
    return 0;
}
