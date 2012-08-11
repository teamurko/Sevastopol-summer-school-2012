#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forv(i, v) forn(i, (v).size())

void printUsage(const char* name)
{
    cerr << "Usage : " << name << " "
        << "max_tests index max_prime max_rem_count" << endl;
}

const int N = 1000 * 1000;
bitset<N> primeset;
vector<int> primes;

void calcPrimes()
{
    primeset.set();
    primeset.set(0);
    primeset.set(1);
    primes.reserve(N / log(N));
    for (int p = 2; p < N; ++p) {
        if (primeset.test(p)) {
            for (int i = p + p; i < N; i += p) {
                primeset.reset(i);
            }
            primes.push_back(p);
        }
    }
}

int main(int argc, char** argv)
{
    srand(1);
    if (argc != 5) {
        printUsage(argv[0]);
        return 1;
    }

    int maxTests = atoi(argv[1]);
    int index = atoi(argv[2]);
    int maxPrime = atoi(argv[3]);
    int maxRemCount = atoi(argv[4]);

    calcPrimes();
    reverse(primes.begin(), primes.end());
    int numTests = 0;
    vector<int> rem, mod;
    forv(i, primes) {
        int p = primes[i];
        if (p > maxPrime) continue;
        if (numTests == maxTests) break;
        vector<int> rems(p - 1);
        for (int i = 1; i < p; ++i) rems[i - 1] = i;
        random_shuffle(rems.begin(), rems.end());
        forv(i, rems) {
            if (numTests == maxTests) break;
            if (i == maxRemCount) break;
            ++numTests;
            rem.push_back(rems[i]);
            mod.push_back(p);
        }
    }

    cout << numTests << endl;
    forv(i, rem) {
        cout << rem[i] << " " << index << " " << mod[i] << endl;
    }

    return 0;
}
