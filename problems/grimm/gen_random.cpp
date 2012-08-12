#include "testlib.h"
#include <iostream>
#include <cstdio>
using namespace std;

void readPrimes(vector<int>* primes)
{
    freopen("primes.txt", "rt", stdin);
    int p;
    primes->reserve(60000000);
    while (scanf("%d", &p) == 1) {
        primes->push_back(p);
    }
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv);

    vector<int> primes;
    readPrimes(&primes);

    int i = rnd.next(0, primes.size() - 2);
    cout << primes[i] << " " << primes[i + 1] << endl;

    return 0;
}
