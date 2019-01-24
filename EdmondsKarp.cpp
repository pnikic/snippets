// Edmonds Karp's algorithm
//
// Calculates the max flow (min cut) of a directed graph.
//
// Variables:
// - G is the adjecency list of the graph.
// - s, t are the source and sink.
// - P is the list of parents in an augmenting path.
// - R is the residual graph.
// - V, E are the numbers of vertices and edges of the graph.
// - MAX is the maximum number of vertices (needs to be configurated).
//
// Functions:
// - AP() finds if there exists an augmenting path from s to t and stores
// the path in P.
// - process(u, v, w) adds an edge from u to v with weight w.
//
// Note: If the problem states that multiple edges between vertices are possible,
// the function process() needs to be configurated.
//
// Time complexity: O(VE ^ 2)

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

#define inf 1e9

typedef vector<int> vi;
typedef vector<vi> vvi;

const int MAX = 5000;

int R[MAX][MAX], V, E, s, t;
vvi G;
vi P;

bool AP()
{
    queue<int> Q;
    P.assign(V, -1);
    Q.push(s);
    while (!Q.empty())
    {
        int k = Q.front(); Q.pop();
        if (k == t)
            return true;

        for (int x : G[k])
            if (P[x] == -1 && R[k][x] > 0)
                P[x] = k, Q.push(x);
    }

    return false;
}

void process(int u, int v, int w)
{
    G[u].push_back(v);
    G[v].push_back(u);
    R[u][v] = w;
}

int main()
{
    memset(R, 0, sizeof(R));
    G.assign(V, vi());

    int MF = 0;
    while (AP())
    {
        int aug = inf;
        for (int x = t; x != s; x = P[x])
            aug = min(aug, R[P[x]][x]);

        for (int x = t; x != s; x = P[x])
            R[P[x]][x] -= aug, R[x][P[x]] += aug;

        MF += aug;
    }
}
