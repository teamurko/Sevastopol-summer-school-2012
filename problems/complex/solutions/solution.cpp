#include <utility>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;

vector<int> buildPrimes(int n)
{
    assert(n > 0);
    vector<bool> used(n, true);
    used[0] = used[1] = false;
    for (int p = 0; p < n; ++p) {
        if (used[p]) {
            for (int i = p + p; i < n; i += p) {
                used[i] = false;
            }
        }
    }
    vector<int> primes;
    primes.reserve(static_cast<int>(n / (log(1.0 * n) + 1)));
    for (int p = 2; p < n; ++p) {
        if (used[p]) {
            primes.push_back(p);
        }
    }
    return primes;
}

pair<long long, long long> ans;

void globalUpdate(long long number, long long complexity)
{
    if (ans.second < complexity || (ans.second == complexity &&
                                    number < ans.first)) {
        ans = make_pair(number, complexity);
    }
}

void brute(long long n, int primeIndex, int degree,
           long long number, long long complexity)
{
    static const vector<int> primes = buildPrimes(10000);
    bool canImprove = false;
    for (int i = 1; i <= degree; ++i) {
        n /= primes.at(primeIndex);
        if (n == 0) break;
        number *= primes[primeIndex];
        canImprove = true;
        brute(n, primeIndex + 1, i, number, complexity * (i + 1));
    }
    if (!canImprove) {
        globalUpdate(number, complexity);
    }
}

/*
pair<long long, long long> solve(long long n)
{
    const static vector<int> primes = buildPrimes(10000);
    pair<long long, long long> result(1, 1);
    for (int k = 1; ; ++k) {
        long long r = n;
        long long number = 1;
        for (int i = 0; i < k; ++i) {
            r /= primes[i];
            if (r == 0) break;
            number *= primes[i];
        }
        if (r == 0) break;
        vector<int> alpha(k, 1);
        for (int i = 0; ; i = (i + 1) % k) {
            r /= primes[i];
            if (r == 0) break;
            number *= primes[i];
            ++alpha[i];
        }
        long long complexity = 1;
        for (int i = 0; i < k; ++i) {
            complexity *= (alpha[i] + 1);
        }
        if (complexity > result.second || (complexity == result.second &&
                                           number < result.first)) {
            result = make_pair(number, complexity);
        }
    }
    return result;
}
*/

int main(int argc, char** argv)
{
    int numTests; cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        long long n; cin >> n;
        ans = make_pair(1, 1);
        brute(n, 0, 20, 1, 1);
        cout << ans.first << " " << ans.second << endl;
    }
    return 0;
}
