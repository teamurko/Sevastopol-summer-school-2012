#include <iostream>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forv(i, v) forn(i, (v).size())

typedef long long ll;
const int NMAX = 205;
const ll P = 1000000009;

ll binom[NMAX][NMAX];
typedef vector<vector<ll> > Matrix;

Matrix mul(const Matrix& a, const Matrix& b)
{
    static Matrix c;
    int n = a.size();
    if (c.empty()) {
        c.resize(n, vector<ll>(n));
    }
    forn(i, n) {
        forn(j, n) {
            c[i][j] = 0;
            forn(k, n) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= P;
            }
        }
    }
    return c;
}

Matrix pow(Matrix a, ll n)
{
    Matrix res(a.size(), vector<ll>(a.size()));
    forv(i, res) res[i][i] = 1;
    while (n > 0) {
        if (n & 1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}

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

int main (int argc, char * const argv[])
{
    ll n; cin >> n;
    int k; cin >> k;
    vector<ll> init(k);
    forn(i, k) cin >> init[i];
    forn(i, k + 1) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % P;
        }
    }
    Matrix a(k, vector<ll>(k));
    forn(i, k-1) a[i + 1][i] = 1;
    for (int i = 1; i <= k; ++i) {
        a[0][i - 1] = binom[k][i];
        if (i % 2 == 0) a[0][i - 1] *= -1;
        a[0][i - 1] = (a[0][i - 1] + P) % P;
    }
    a = pow(a, n - k + 1);

    ll ans = 0;
    forn(i, k) {
        ans += init[k - i - 1] * a[0][i];
        ans %= P;
    }
    cout << ans << endl;

    return 0;
}
