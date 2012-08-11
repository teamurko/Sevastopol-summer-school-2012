#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
vector<ll> pow5;

ll mul(ll a, ll b, ll m)
{
    ll result = 0;
    while (b > 0) {
        if (b & 1) {
            result = (result + a) % m;
        }
        a = (a + a) % m;
        b >>= 1;
    }
    return result;
}

ll pow(ll a, ll n, ll m)
{
    ll result = 1 % m;
    while (n > 0) {
        if (n & 1) {
            result = mul(result, a, m);
        }
        a = mul(a, a, m);
        n >>= 1;
    }
    return result;
}

ll calc(int p, int zwei, int funf, int n)
{
    if (n == 1) {
        ll m = (1LL << zwei) * pow5.at(funf);
        return p % m;
    }
    if (zwei == 0 && funf == 0) {
        return 0;
    }
    ll m = funf == 0 ? calc(p, zwei - 1, 0, n - 1) :
                       calc(p, zwei + 1, funf - 1, n - 1);
    return pow(p, m, (1LL << zwei) * pow5.at(funf));
}

int main (int argc, char * const argv[])
{
    pow5.resize(20);
    for (int i = 0; i < pow5.size(); ++i) {
        pow5[i] = i == 0 ? 1 : pow5[i - 1] * 5;
    }
    int n, p;
    cin >> p >> n;
    cout << calc(p, 16, 16, n) << endl;
    return 0;
}
