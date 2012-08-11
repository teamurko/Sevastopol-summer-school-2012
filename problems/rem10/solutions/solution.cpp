#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
vector<ll> pow5;

ll pow(ll a, ll n, ll m)
{
    ll result = 1 % m;
    while (n > 0) {
        if (n & 1) {
            result = (result * a) % m;
        }
        a *= a;
        a %= m;
        n >>= 1;
    }
    return result;
}

ll calc(int zwei, int funf, int n)
{
    if (n == 1) {
        ll m = (1LL << zwei) * pow5.at(funf);
        return 19 % m;
    }
    if (zwei == 0 && funf == 0) {
        return 0;
    }
    ll m = funf == 0 ? calc(zwei - 1, 0, n - 1) :
                       calc(zwei + 1, funf - 1, n - 1);
    return pow(19, m, (1LL << zwei) * pow5.at(funf));
}

int main (int argc, char * const argv[])
{
    pow5.resize(20);
    for (int i = 0; i < pow5.size(); ++i) {
        pow5[i] = i == 0 ? 1 : pow5[i - 1] * 5;
    }
    int n, k;
    cin >> k >> n;
    cout << calc(k, k, n) << endl;
    return 0;
}
