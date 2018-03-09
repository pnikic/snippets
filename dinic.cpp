// Dinic's algorithm
//
// Calculates the max flow (min cut) of a directed graph.
//
// Variables:
// - G is the adjecency list of the graph.
// - s, t are the source and sink.
// - D is the list of distances from s in the level graph.
// - R is the residual graph.
// - V, E are the numbers of vertices and edges of the graph.
// - MAX is the maximum number of vertices (needs to be configurated).
//
// Functions:
// - LevelGraph() finds if there exists an augmenting path from s to t and stores
// distances from s in D
// - Push() finds an augmenting path from s to t in the level graph and augments the flow
// - process(u, v, w) adds an edge from u to v with weight w.
//
// Note: If the problem states that multiple edges between vertices are possible,
// the function process() needs to be configurated.
//
// Time complexity: O(EV^2)

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

#define inf 1e9

typedef vector<int> vi;
typedef vector<vi> vvi;

const int MAX = 100;

int R[MAX][MAX], D[MAX], V, E, s, t, u = 1;
vvi G;

int Push(int x, int flow)
{
    if (x == t)
        return flow;
    for (int y : G[x])
        if (R[x][y] > 0 && D[y] == D[x] + 1)
            if (int f = Push(y, min(flow, R[x][y])))
                return R[x][y] -= f, R[y][x] += f, f;
    return D[x] = -1, 0;
}

bool LevelGraph()
{
    queue<int> Q;
    Q.push(s);
    memset(D, -1, sizeof(D));
    D[s] = 0;
    while (!Q.empty())
    {
        int k = Q.front(); Q.pop();
        if (k == t) return true;
        for (int x : G[k])
            if (D[x] == -1 && R[k][x] > 0)
                D[x] = D[k] + 1, Q.push(x);
    }
    return false;
}

void process(int u, int v, int w)
{
    G[u].push_back(v);
    G[v].push_back(u);
    R[u][v] += w;
}

int main()
{
    memset(R, 0, sizeof(R));
    G.assign(V, vi());

    int MF = 0;
    while (LevelGraph())
        while (int f = Push(s, inf))
            MF += f;
}
