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

int phi(int n)
{
    int result = 1;
    for (int p = 2; p * p <= n; ++p) {
        int cnt = 0;
        while (n % p == 0) {
            ++cnt;
            n /= p;
        }
        if (cnt > 0) {
            result *= (p - 1);
        }
        for (int i = 1; i < cnt; ++i) {
            result *= p;
        }
    }
    if (n > 1) {
        result *= n - 1;
    }
    return result;
}

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

std::vector<int> primeDivisors(int n)
{
    const static int N = 33000;
    const static std::vector<int> cache =
                 extractPrimes(leastPrimeDivisors(N));

    std::vector<int> result;
    result.reserve(1000);
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

int table[33000];
int values[1000];
int shift = -10000000;
const int NMAX = 100005;
std::vector<int> ans[NMAX];

//Returns UNDEFINED iff there is no solution.
//It works, but is not optimized.
int log(int g, int a, int n)
{
    REQUIRE(n >= 1, "n should be >= 1, but "
            << n << " is provided");
    REQUIRE(gcd(g, n) == 1, "base and module should be coprime");
    int h = phi(n);
    a %= n;
    int m = static_cast<int>(sqrt(h * 1.0) + 1e-4);
    int cur = 1;
    int b = pow(g, m, n);

    for (int i = 0; i < h / m + 3; ++i) {
        if (cur == 1 && i > 0) {
            break;
        }
        table[cur] = i + shift;
        cur = (cur * b) % n;
    }
    cur = a;
    for (int i = 0; i < m + 1; ++i) {
        if (cur == a && i > 0) {
            break;
        }
        if (table[cur] >= shift) {
            int result = ((table[cur] - shift) * m - i + h) % h;
            REQUIRE(pow(g, result, n) == a, "Logic error: g x a n "
                    << g << " " << result << " " << a << " " << n);
            shift += 2 * m + 2;
            return result;
        }
        cur = (cur * g) % n;
    }
    shift += 2 * m + 2;
    return UNDEFINED;
}

//This function itself does work, but is not optimized.
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

template <class Iter>
void solve(Iter begin, Iter end, int deg)
{
    int n = begin->first;
    int gp = primitiveRoot(n);
    int h = phi(n);
    int g = pow(gp, deg, n);
    static const int M = 700;
    const int hm = (h + M - 1) / M;
    int b = pow(g, hm, n);
    int cur = b;
    for (int i = 1; i <= M; ++i) {
        table[cur] = i + shift;
        cur = (cur * b) % n;
    }

    while (begin != end) {
        int a = begin->second.first;
        int id = begin->second.second;
        ++begin;

        int cur = (a * g) % n;
        int x0 = UNDEFINED;
        for (int i = 1; i <= hm; ++i) {
            if (table[cur] > shift) {
                x0 = (table[cur] - shift) * hm - i;
                assert(x0 >= 0);
                break;
            }
            cur = (cur * g) % n;
        }
        if (x0 != UNDEFINED) {
            for (int l = 0; l < deg; ++l) {
                if (h * l % deg == 0) {
                    ans[id].push_back(pow(gp, x0 + h * l / deg, n));
                }
            }
        }
    }
    shift += M;
}

int main (int argc, char * const argv[])
{
    std::ios_base::sync_with_stdio(false);
    for (int i = 0; i < 33000; ++i) {
        table[i] = shift - 1;
    }
    int numTests; std::cin >> numTests;
    typedef std::pair<int, std::pair<int, int> > Node;
    std::vector<Node> tests(numTests);
    for (int test = 0; test < numTests; ++test) {
        int a, n; std::cin >> a >> n;
        tests[test].first = n;
        tests[test].second = std::make_pair(a, test);
    }
    std::sort(tests.begin(), tests.end());
    for (int l = 0; l < numTests; ) {
        int r = l + 1;
        while (r < numTests && tests[r].first == tests[l].first) ++r;
        solve(tests.begin() + l, tests.begin() + r, 2);
        l = r;
    }
    for (int i = 0; i < numTests; ++i) {
        std::sort(ans[i].begin(), ans[i].end());
        if (ans[i].empty()) {
            std::cout << "No root" << std::endl;
        } else {
            for (size_t j = 0; j < ans[i].size(); ++j) {
                if (j) std::cout << " ";
                std::cout << ans[i][j];
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
