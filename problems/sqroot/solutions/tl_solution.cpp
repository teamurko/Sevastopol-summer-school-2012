#include <map>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

const int UNDEFINED = -1;
#define REQUIRE(cond, message) \
    do { \
        if (!(cond)) { \
            std::cerr << message << std::endl; \
            assert(false); \
        } \
    } while (0)

int gcd(int a, int b)
{
    return a == 0 ? b : gcd(b % a, a);
}

inline
int pow(int a, int n, int m)
{
    int p = a % m;
    int result = 1 % m;
    while (n > 0) {
        if (n & 1) {
            result = (result * p) % m;
        }
        p = (p * p) % m;
        n >>= 1;
    }
    return result;
}

inline
std::vector<std::pair<int, int> > factor(int n)
{
    std::vector<std::pair<int, int> > result;
    result.reserve(10);
    for (int p = 2; p * p <= n; ++p) {
        int cnt = 0;
        while (n % p == 0) {
            ++cnt;
            n /= p;
        }
        if (cnt > 0) {
            result.push_back(std::make_pair(p, cnt));
        }
    }
    if (n > 1) {
        result.push_back(std::make_pair(n, 1));
    }
    return result;
}

inline
int phi(int n)
{
    int result = 1;
    std::vector<std::pair<int, int> > f = factor(n);
    for (size_t i = 0; i < f.size(); ++i) {
        const std::pair<int, int>& pc = f[i];
        result *= pc.first - 1;
        for (int j = 0; j < pc.second - 1; ++j) {
            result *= pc.first;
        }
    }
    return result;
}

inline
std::vector<int> leastPrimeDivisors(int n)
{
    std::vector<int> result(n);
    result[1] = 1;
    for (int p = 2; p < n; ++p) {
        if (result[p] > 0) continue;
        result[p] = p;
        for (int i = p + p; i < n; i += p) {
            if (result[i] == 0) {
                result[i] = p;
            }
        }
    }
    return result;
}

inline
std::vector<int> extractPrimes(const std::vector<int>& leastPrimeDivisors)
{
    std::vector<int> result;
    result.reserve(10);
    for (int p = 2; p < static_cast<int>(leastPrimeDivisors.size()); ++p) {
        if (p == leastPrimeDivisors[p]) {
            result.push_back(p);
        }
    }
    return result;
}

inline
std::vector<int> primeDivisors(int n)
{
    const static int N = 100000;
    const static std::vector<int> cache =
                 extractPrimes(leastPrimeDivisors(N));

    std::vector<int> result;
    for (size_t i = 0; i < cache.size(); ++i) {
        int prime = cache[i];
        if (prime * prime > n) break;
        if (n % prime == 0) {
            result.push_back(prime);
        }
        while (n % prime == 0) {
            n /= prime;
        }
    }
    if (n > 1) {
        result.push_back(n);
    }
    return result;
}

inline
int primitiveRoot(int n)
{
    REQUIRE(n > 1, "Primitive root can be calculated for n > 1, but "
                    << n << " provided");
    if (n == 2) return 1;
    int ph = phi(n);
    const std::vector<int> divisors = primeDivisors(ph);
    bool isPrimitive = false;
    int g = 1;
    do {
        ++g;
        isPrimitive = true;
        for (size_t i = 0; i < divisors.size(); ++i) {
            int d = divisors[i];
            if (pow(g, ph / d, n) == 1) {
                isPrimitive = false;
                break;
            }
        }
    } while (!isPrimitive);
    REQUIRE(gcd(n, g) == 1, "Primitive root and module "
            << "should be coprime");
    return g;
}

inline
std::vector<int> powers(int a, int m, int n)
{
    std::vector<int> result(m);
    int current = 1 % n;
    for (int i = 0; i < m; ++i) {
        result[i] = current;
        current = (current * a) % n;
    }
    return result;
}

//Returns UNDEFINED iff there is no solution.
int log(int g, int a, int n)
{
    REQUIRE(n >= 1, "n should be >= 1, but "
            << n << " is provided");
    REQUIRE(gcd(g, n) == 1, "base and module should be coprime");
    int h = phi(n);
    int m = static_cast<int>(sqrt(h * 1.0) + 1e-4);
    std::vector<int> largep = powers(pow(g, m, n), h / m + 3, n);
    std::map<int, int> table;
    for (size_t i = 0; i < largep.size(); ++i) {
        table[largep[i]] = i;
    }
    std::vector<int> smallp = powers(g, m + 3, n);
    for (int i = 0; i < static_cast<int>(smallp.size()); ++i) {
        int rightPart = (smallp[i] * a) % n;
        if (table.count(rightPart)) {
            int result = ((table[rightPart] * m - i) % h + h) % h;
            REQUIRE(pow(g, result, n) == a % n, "Logic error: g x a n "
                    << g << " " << result << " " << a << " " << n);
            return result;
        }
    }
    return UNDEFINED;
}

std::vector<int> roots(int a, int deg, int n)
{
    REQUIRE(gcd(a, n) == 1, "a and n should be coprime, but gcd(a, n) = "
            << gcd(a, n));
    REQUIRE(deg >= 2, "degree should not be degenerate, but "
            << deg << " is provided");
    int g = primitiveRoot(n);
    int h = phi(n);
    int x0 = log(pow(g, deg, n), a, n);
    std::vector<int> result;
    if (x0 != UNDEFINED) {
        for (int l = 0; l < deg; ++l) {
            if (h * l % deg == 0) {
                result.push_back(pow(g, x0 + h * l / deg, n));
            }
        }
    }
    return result;
}

int main (int argc, char * const argv[])
{
    std::ios_base::sync_with_stdio(false);
    int numTests; std::cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        int a, n; std::cin >> a >> n;
        std::vector<int> ans = roots(a, 2, n);
        std::sort(ans.begin(), ans.end());
        if (ans.empty()) {
            std::cout << "No root" << std::endl;
        } else {
            for (size_t i = 0; i < ans.size(); ++i) {
                if (i) std::cout << " ";
                std::cout << ans[i];
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
