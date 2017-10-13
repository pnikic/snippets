// Min Cost Max Flow
//
// Computes the minimum cost of producing max flow. Used Bellman Ford's
// SSSP to detect and cancel negative cycles.
//
// Variables:
// - V, E are the number of vertices and edges in the graph.
// - s, t are the source and the sink.
// - G is the adjecency list of the graph.
// - C[u][v] is the cost of running 1 flow from u to v.
// - R is the residual graph.
// - dist is the vector of distances from the sink to other vertices
// through the residual graph.
// - P[x] is the predecessor of x in an augmenting path/SSSP.
//
// Functions:
// - MinCostMaxFlow computes the max flow and min cost for that particular flow.
// - ap() return true if there exists an augmenting path from s to t.
// - HasCycle() detects whether there exists a negative cycle from t to s
// using the residual graph:
//
// Time complexity: O((V E) ^ 2)
//
// Note: the code can be adjusted so that we look for a particular flow F.
// Before updating MF in the MinCostMaxFlow function, check whether
// it will exceed F then add just enough such that MF + aug = F. 

#include <iostream>
#include <vector>
#include <cstring>
#include <tuple>
#include <queue>

using namespace std;

#define inf 1e9

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int MAX = 100;

int R[MAX][MAX], C[MAX][MAX], V, E, s, t;
vi dist, P;
vvi G;

bool ap()
{
    queue<int> Q;
    Q.push(s);
    P.assign(V, -1);
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

int HasCycle()
{
    dist.assign(V, inf);
    P.assign(V, -1);
    dist[t] = 0;
    for (int k = 0; k < V - 1; ++k)
        for (int u = 0; u < V; ++u)
            for (int v : G[u])
                if (R[u][v] > 0 && dist[v] > dist[u] + C[u][v])
                    dist[v] = dist[u] + C[u][v], P[v] = u;

    bool fl = false;
    for (int u = 0; u < V; ++u)
        for (int v : G[u])
            if (R[u][v] > 0 && dist[v] > dist[u] + C[u][v])
                fl = true;

    if (fl)
    {
        vi vis(V, 0);
        int x = s;
        vis[x] = true;
        for (int i = 0; i < V; ++i)
        {
            x = P[x];
            if (x == -1)
                return -1;
            
            if (vis[x])
                return x;
            
            vis[x] = true;
        }
    }
    
    return -1;
}

ii MinCostMaxFlow()
{
    int MF = 0, MC = 0;
    while (ap())
    {
        int aug = inf;
        for (int x = t; x != s; x = P[x])
            aug = min(aug, R[P[x]][x]);

        for (int x = t; x != s; x = P[x])
            R[P[x]][x] -= aug, R[x][P[x]] += aug, MC += C[P[x]][x] * aug;

        MF += aug;
    }

    int u;
    while (u = HasCycle(), u != -1)
    {
        int aug = R[P[u]][u], cost = 0;
        for (int x = P[u]; x != u; x = P[x])
            aug = min(aug, R[P[x]][x]);
        
        R[P[u]][u] -= aug;
        R[u][P[u]] += aug;
        MC += C[P[u]][u] * aug;
        for (int x = P[u]; x != u; x = P[x])
            R[P[x]][x] -= aug, R[x][P[x]] += aug, MC += C[P[x]][x] * aug;
    }
    
    return {MF, MC};
}

void process(int u, int v, int w, int c)
{
    R[u][v] = w;
    C[u][v] = c, C[v][u] = -c;
    G[u].push_back(v);
    G[v].push_back(u);
}

int main()
{
    memset(R, 0, sizeof(R));
    memset(C, 0, sizeof(C));
    cin >> V >> E;
    G.assign(V, vi());
    for (int i = 0; i < E; ++i)
    {
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        process(u, v, w, c);
    }
    cin >> s >> t;
    int MC, MF;
    tie(MF, MC) = MinCostMaxFlow();
    cout << MC << ' ' << MF << endl;
}
