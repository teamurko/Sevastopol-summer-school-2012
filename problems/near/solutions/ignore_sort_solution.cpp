#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

#define forn(i, n) for (int i = 0; i < static_cast<int>(n); ++i)
#define forv(i, v) forn(i, (v).size())

typedef vector<vector<int> > Graph;

const int INF = 1e7;
Graph graph;
vector<string> names;
vector<int> dates;
vector<int> sizes;
vector<int> parent;
int numNodes, root;
int source, target, sortTime;

void readData()
{
    cin >> numNodes >> sortTime;
    graph.resize(numNodes);
    names.resize(numNodes);
    dates.resize(numNodes);
    sizes.resize(numNodes);
    parent.resize(numNodes, -1);
    root = -1;
    forn(i, numNodes) {
        int par;
        cin >> par >> names[i] >> sizes[i] >> dates[i];
        if (par == -1) {
            assert(root == -1);
            root = i;
        } else {
            graph[par].push_back(i);
            parent[i] = par;
        }
    }
    cin >> source >> target;
}

bool cmpByName(int i, int j)
{
    return names[i] < names[j];
}

int lca(int v, int u)
{
    set<int> parents;
    while (v != -1) {
        parents.insert(v);
        v = parent[v];
    }
    while (parents.count(u) == 0) {
        u = parent[u];
    }
    return u;
}

int indexOf(const vector<int>& vertices, int id)
{
    int ret = find(vertices.begin(), vertices.end(), id) - vertices.begin();
    assert(ret < static_cast<int>(vertices.size()));
    return ret;
}

void solve()
{
    if (source == target) {
        cout << 0 << endl;
        return;
    }
    forn(i, numNodes) {
        sort(graph[i].begin(), graph[i].end(), &cmpByName);
    }
    int p = lca(source, target);
    int ans = 0;
    int u = source, v = target;
    if (u != p) {
        while (parent[u] != p) {
            ans += indexOf(graph[parent[u]], u);
            ans += 2;
            u = parent[u];
        }
    }
    if (v != p) {
        while (parent[v] != p) {
            ans += indexOf(graph[parent[v]], v);
            ans += 2;
            v = parent[v];
        }
    }
    if (v == p) {
        ans += indexOf(graph[v], u);
        ans += 2;
    } else if (u == p) {
        ans += indexOf(graph[u], v);
        ans += 2;
    } else {
        ans += abs(indexOf(graph[p], u) - indexOf(graph[p], v));
    }
    cout << ans << endl;
}

int main (int argc, char * const argv[])
{
    readData();
    solve();
    return 0;
}
