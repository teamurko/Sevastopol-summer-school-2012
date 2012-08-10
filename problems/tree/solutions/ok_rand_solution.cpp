#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <cmath>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forv(i, v) forn(i, v.size())

typedef vector<vector<int> > Graph;
const int UNDEFINED = -1;
const int MOD = 1000000007;
const int P = 127;

void readData(Graph* graph, vector<int>* values, int& root)
{
    int numVertices;
    cin >> numVertices;
    graph->resize(numVertices);
    values->resize(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        int parent, value;
        cin >> parent >> value;
        if (parent != UNDEFINED) {
            assert(parent >= 0);
            graph->at(parent).push_back(i);
        } else {
            root = i;
        }
        values->at(i) = value;
    }
}

set<int>* merge(set<int>* first, set<int>* second, int& ans)
{
    if (first->size() < second->size()) {
        swap(first, second);
    }
    cerr << "mergin " << first->size() << " to " << second->size() << endl;
    for (set<int>::const_iterator it = first->begin();
                                  it != first->end();
                                  ++it) {
        set<int>::const_iterator fit = second->lower_bound(*it);
        if (fit != second->end()) {
            ans = min(ans, abs(*it - *fit));
        }
        if (fit != second->begin()) {
            --fit;
            ans = min(ans, abs(*it -*fit));
        }
    }
    second->insert(first->begin(), first->end());
    first->clear();
    return second;
}

void dfs(int vertex, const Graph& graph,
         const vector<int>& values,
         vector<set<int>*>* table,
         vector<int>* ans)
{
    if (graph[vertex].size() == 0) {
        table->at(vertex) = new set<int>();
        table->at(vertex)->insert(values[vertex]);
        return;
    }
    int localAns = MOD;
    forv(i, graph[vertex]) {
        int child = graph[vertex][i];
        dfs(child, graph, values, table, ans);
        localAns = min(localAns, ans->at(child));
    }
    set<int>* cur = table->at(graph[vertex].front());
    for (size_t i = 1; i < graph[vertex].size(); ++i) {
        int child = graph[vertex][i];
        cur = merge(cur, table->at(child), localAns);
    }
    set<int>::const_iterator it = cur->lower_bound(values[vertex]);
    if (it != cur->end()) {
        localAns = min(localAns, abs(values[vertex] - *it));
    }
    if (it != cur->begin()) {
        --it;
        localAns = min(localAns, abs(values[vertex] - *it));
    }
    cur->insert(values[vertex]);
    table->at(vertex) = cur;
    ans->at(vertex) = localAns;
}

void solve(const Graph& graph, const vector<int>& values, int root)
{
    vector<set<int>*> table(graph.size());
    vector<int> ans(graph.size(), MOD);
    dfs(root, graph, values, &table, &ans);
    long long Ans = 0;
    forv(i, graph) {
        Ans = (Ans * P + ans[i]) % MOD;
    }
    cout << Ans << endl;
}

int main (int argc, char * const argv[])
{
    ios_base::sync_with_stdio(false);
    Graph graph;
    vector<int> values;
    int root;
    readData(&graph, &values, root);
    solve(graph, values, root);
    return 0;
}
