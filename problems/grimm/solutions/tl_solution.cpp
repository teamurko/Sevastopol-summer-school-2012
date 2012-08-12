#include <cassert>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forv(i, v) forn(i, (v).size())

void get_prime_divisors(int n, vector<int>* result)
{
    result->clear();
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            result->push_back(p);
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) result->push_back(n);
}

const int GAP_MAX = 1000;
vector<int> facts[GAP_MAX];

bool brute(int idx, int n, set<int>& taken, vector<int>& ans)
{
    if (idx == n) {
        forv(i, ans) {
            if (i) cout << " ";
            cout << ans[i];
        }
        cout << endl;
        return true;
    }
    forv(i, facts[idx]) {
        int pd = facts[idx][i];
        if (!taken.count(pd)) {
            taken.insert(pd);
            ans.push_back(pd);
            if (brute(idx + 1, n, taken, ans)) return true;
            ans.pop_back();
            taken.erase(pd);
        }
    }
    return false;
}

void solve(int l, int r)
{
    assert(l <= r);
    for (int i = l; i <= r; ++i) {
        get_prime_divisors(i, &facts[i - l]);
//        random_shuffle(facts[i - l].begin(), facts[i - l].end());
    }
    set<int> st;
    vector<int> ans;
    ans.reserve(r - l + 1);
    assert(brute(0, r - l + 1, st, ans));
}

int main (int argc, char * const argv[])
{
    int p1, p2;
    cin >> p1 >> p2;
    solve(p1 + 1, p2 - 1);
    return 0;
}
