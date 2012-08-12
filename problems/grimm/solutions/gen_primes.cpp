#include <cassert>
#include <iostream>
#include <vector>
#include <set>
#include <bitset>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forv(i, v) forn(i, (v).size())
const int N = 100 * 1000 * 1000;
const int SQN = 100 * 1000;
bitset<N> prime;

int main (int argc, char * const argv[])
{
    ios_base::sync_with_stdio(false);
    prime.set();
    prime.reset(0);
    prime.reset(1);
    vector<int> primes;
    for (int i = 2; i < SQN; ++i) {
        if (prime.test(i)) {
            primes.push_back(i);
            for (int j = i + i; j < SQN; j += i) {
                prime.reset(j);
            }
        }
    }
    int shift = 0;
    forn(i, 10) {
        prime.set();
        forv(j, primes) {
            int p = primes[j];
            for (int x = (shift + p - 1) / p * p - shift; x < N; x += p) {
                if (x == p) continue;
                prime.reset(x);
            }
        }
        forn(j, N) {
            if (i * N + j < 2) continue;
            if (prime.test(j)) {
                cout << shift + j << " ";
            }
        }
        shift += N;
    }
    return 0;
}
