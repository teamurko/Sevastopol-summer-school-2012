#include "testlib.h"
#include <vector>
#include <queue>
#include <string>
using namespace std;
#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forv(i, v) forn(i, v.size())

typedef vector<vector<pair<string, int> > > Graph;

int main()
{
    registerValidation();
    int numVertices = inf.readInt(1, 40000);
    inf.readSpace();
    int sortTime = inf.readInt(0, 10);
    inf.readEoln();
    Graph graph(numVertices);
    int root = -1;
    for (int i = 0; i < numVertices; ++i) {
        int parent = inf.readInt(-1, numVertices - 1);
        inf.readSpace();
        string name = inf.readToken("[a-zA-Z]{1,10}", "name");
        inf.readSpace();
        inf.readInt(0, 10000);
        inf.readSpace();
        inf.readInt(0, 10000);
        inf.readEoln();
        if (parent == -1) {
            ensure(root == -1);
            root = i;
        } else {
            graph[parent].push_back(make_pair(name, i));
        }
    }
    ensure(root != -1);
    queue<int> q;
    q.push(root);
    int reachedCount = 0;
    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        ++reachedCount;
        forv(i, graph[vertex]) {
            q.push(graph[vertex][i].second);
        }
    }
    ensure(reachedCount == numVertices);

    forv(v, graph) {
        vector<pair<string, int> >& lst = graph[v];
        sort(lst.begin(), lst.end());
        forv(i, lst) {
            if (i > 0) {
                ensure(lst[i - 1].first != lst[i].first);
            }
        }
    }
    inf.readInt(0, numVertices - 1);
    inf.readSpace();
    inf.readInt(0, numVertices - 1);
    inf.readEoln();
    inf.readEof();

    return 0;
}
