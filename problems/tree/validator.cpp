#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;
#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forv(i, v) forn(i, v.size())

typedef vector<vector<int> > Graph;

int main()
{
    registerValidation();
    int numVertices = inf.readInt(1, 40000);
    inf.readEoln();
    Graph graph(numVertices);
    int root = -1;
    for (int i = 0; i < numVertices; ++i) {
        int parent = inf.readInt(-1, numVertices - 1);
        inf.readSpace();
        int value = inf.readInt(0, 1000000);
        inf.readEoln();
        if (parent == -1) {
            ensure(root == -1);
            root = i;
        } else {
            graph[parent].push_back(i);
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
            q.push(graph[vertex][i]);
        }
    }
    ensure(reachedCount == numVertices);

    return 0;
}
