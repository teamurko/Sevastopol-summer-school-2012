#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forv(i, v) forn(i, (v).size())
#define for1(i, n) for (int i = 1; i <= int(n); ++i)

typedef long long ll;
const int NMAX = 205;
const ll P = 1000000009;

typedef vector<vector<ll> > Matrix;

void print(const Matrix& a)
{
    int n = a.size();
    forn(i, n) {
        forn(j, n) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

ll pow(ll x, ll n)
{
    ll res = 1 % P;
    while (n > 0) {
        if (n & 1) {
            res = (res * x) % P;
        }
        x = (x * x) % P;
        n >>= 1;
    }
    return res;
}

ll rev(ll x)
{
    x %= P;
    assert(x != 0);
    return pow(x, P - 2);
}

vector<ll> gauss(Matrix a)
{
    int n = a.size();
    forn(i, n) {
        int bi = i;
        while (bi < n && a[bi][i] == 0) {
            ++bi;
        }
        assert(bi < n);
        if (bi != i) {
            for (int j = i; j <= n; ++j) {
                swap(a[bi][j], a[i][j]);
            }
        }
        assert(a[i][i] != 0);
        for (int j = i + 1; j < n; ++j) {
            if (a[j][i] == 0) continue;
            ll d = a[j][i];
            for (int k = i; k <= n; ++k) a[j][k] = (a[j][k] * a[i][i]) % P;
            for (int k = i; k <= n; ++k) {
                a[j][k] = ((a[j][k] - a[i][k] * d) % P + P) % P;
            }
            assert(a[j][i] == 0);
        }
    }
    vector<ll> c(n);
    for (int i = n - 1; i >= 0; --i) {
        c[i] = a[i][n];
        for (int j = i + 1; j < n; ++j) {
            c[i] = ((c[i] - a[i][j] * c[j] % P) + P) % P;
        }
        c[i] = (c[i] * rev(a[i][i])) % P;
    }
    return c;
}

int main (int argc, char * const argv[])
{
    ll n; cin >> n;
    int k; cin >> k;

    Matrix a(k, vector<ll>(k + 1));
    forn(i, k) {
        a[i][0] = 1;
        for1(j, k - 1) {
            a[i][j] = (a[i][j - 1] * i) % P;
        }
        cin >> a[i][k];
    }

    vector<ll> c = gauss(a);

    ll ans = 0;
    n %= P;
    forn(i, k) {
        ll t = 1;
        forn(j, i) {
            t = (t * n) % P;
        }
        ans += c[i] * t;
        ans %= P;
    }
    cout << ans << endl;

    return 0;
}
