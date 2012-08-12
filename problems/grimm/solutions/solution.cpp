#include <cassert>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forv(i, v) forn(i, (v).size())

void getPrimeDivisors(int n, vector<int>* result)
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

typedef vector<vector<int> > Graph;

int indexOf(const vector<int>& sorted, int value)
{
    int ret = lower_bound(sorted.begin(), sorted.end(), value)
              - sorted.begin();
    assert(ret < (int)sorted.size());
    return ret;
}

bool tryKhun(int vertex, const Graph& graph,
             vector<bool>& used, vector<int>& matching)
{
    if (used[vertex]) return false;
    used[vertex] = true;
    forv(i, graph[vertex]) {
        int u = graph[vertex][i];
        if (matching[u] == -1 ||
                            tryKhun(matching[u], graph, used, matching)) {
            matching[u] = vertex;
            return true;
        }
    }
    return false;
}

void solve(int l, int r)
{
    assert(l <= r);
    vector<int> primeDivisors;
    for (int i = l; i <= r; ++i) {
        getPrimeDivisors(i, &facts[i - l]);
        primeDivisors.insert(primeDivisors.end(),
                             facts[i - l].begin(),
                             facts[i - l].end());
    }
    sort(primeDivisors.begin(), primeDivisors.end());
    primeDivisors.erase(unique(primeDivisors.begin(), primeDivisors.end()),
                        primeDivisors.end());
    int n = r - l + 1;
    Graph graph(n);
    forn(i, n) {
        forv(j, facts[i]) {
            graph[i].push_back(indexOf(primeDivisors, facts[i][j]));
        }
    }
    vector<int> matching(primeDivisors.size(), -1);
    vector<bool> used(n);
    forn(i, n) {
        forn(j, n) used[j] = false;
        tryKhun(i, graph, used, matching);
    }
    vector<int> ans(n);
    forv(i, matching) {
        if (matching[i] != -1) {
            ans[matching[i]] = primeDivisors[i];
        }
    }
    forv(i, ans) {
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << endl;
}

int main (int argc, char * const argv[])
{
    int p1, p2;
    cin >> p1 >> p2;
    solve(p1 + 1, p2 - 1);
    return 0;
}
