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
vector<int> up[3];
vector<int> down[3];
vector<int> first[3];
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

bool cmpBySize(int i, int j)
{
    if (sizes[i] != sizes[j]) {
        return sizes[i] < sizes[j];
    }
    return names[i] < names[j];
}

bool cmpByDate(int i, int j)
{
    if (dates[i] != dates[j]) {
        return dates[i] < dates[j];
    }
    return names[i] < names[j];
}

void precalc()
{
    typedef bool(*Cmp)(int, int);
    vector<Cmp> cmps(3);
    cmps[0] = &cmpByName;
    cmps[1] = &cmpBySize;
    cmps[2] = &cmpByDate;
    forn(i, 3) {
        up[i].resize(numNodes, -1);
        down[i].resize(numNodes, -1);
        first[i].resize(numNodes, -1);
        forn(vertex, numNodes) {
            if (graph[vertex].empty()) continue;
            vector<int>& lst = graph[vertex];
            sort(lst.begin(), lst.end(), cmps[i]);
            forv(j, lst) {
                if (j > 0) {
                    up[i][lst[j]] = lst[j - 1];
                }
                if (j + 1 < static_cast<int>(lst.size())) {
                    down[i][lst[j]] = lst[j + 1];
                }
            }
            first[i][vertex] = lst.front();
        }
    }
}

struct Edge
{
    Edge() : v(-1), w(0) { }
    Edge(int v_, int w_) : v(v_), w(w_) { }
    int v, w;
};
typedef vector<vector<Edge> > Graph2;
vector<int> dist;

struct Cmp
{
    bool operator()(int i, int j) const
    {
        if (dist[i] != dist[j]) {
            return dist[i] < dist[j];
        }
        return i < j;
    }
};

int dijkstra(const Graph2& graph, int source, int target)
{
    dist.resize(graph.size(), INF);
    dist.at(source) = 0;
    set<int, Cmp> q;
    q.insert(source);
    while (!q.empty()) {
        int v = *q.begin();
        q.erase(v);
        if (target <= v && v < target + 3) {
            return dist[v];
        }
        forv(i, graph[v]) {
            const Edge& e = graph[v][i];
            int dst = dist[v] + e.w;
            if (dist[e.v] > dst) {
                q.erase(e.v);
                dist[e.v] = dst;
                q.insert(e.v);
            }
        }
    }
    assert(false);
}

void solve()
{
    precalc();
    Graph2 graph2(numNodes * 6);
    // 6 * i -- outer node by name, by size, by date
    // 6 * i + 3 -- inner node by name, by size, by date
    forv(v, graph) {
        int outer = 6 * v;
        int inner = outer + 3;
        forn(i, 3) {
            graph2[outer + i].push_back(Edge(inner, 1));
            graph2[inner + i].push_back(Edge(outer, 1));
        }
        forn(i, 3) {
            int u = up[i][v];
            if (u == -1) {
                if (parent[v] != -1) {
                    assert(parent[v] < numNodes);
                    graph2[outer + i].push_back(
                                      Edge(6 * parent[v] + 3 + i, 1));
                }
            } else {
                assert(u < numNodes);
                graph2[outer + i].push_back(Edge(6 * u + i, 1));
            }
            int d = down[i][v];
            if (d != -1) {
                assert(d < numNodes);
                graph2[outer + i].push_back(Edge(6 * d + i, 1));
            }
            if (first[i][v] != -1) {
                assert(first[i][v] < numNodes);
                graph2[inner + i].push_back(Edge(6 * first[i][v] + i, 1));
            }
            forn(j, 3) {
                if (i == j) continue;
                graph2[outer + i].push_back(Edge(outer + j, sortTime));
                graph2[inner + i].push_back(Edge(inner + j, sortTime));
            }
        }
    }
    cout << dijkstra(graph2, 6 * source, 6 * target) << endl;
}

int main (int argc, char * const argv[])
{
    readData();
    solve();
    return 0;
}
